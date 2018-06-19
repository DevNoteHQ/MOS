
#include "heap.hpp"

namespace Heap
{
	uint64_t InitHeapSpace[HEAP_SIZE] __attribute__((aligned(ALIGN2M)));
	HeapDynHeader *InitHeap = (HeapDynHeader *) &InitHeapSpace;

	void Init()
	{
		HeapDynFreePointer *Free = &InitHeap->Free[0];
		uint64_t HeapEnd = ((uint64_t)InitHeap) + HEAP_SIZE * 8;
		memset(InitHeap, 0, HEAP_SIZE * 8);
		InitHeap->End = (uint8_t *)HeapEnd; //Points to the end of the Heap.

		Free[0].First = (HeapElement *)(&Free[FREE_SIZE / 2]); //Always points to the highest, not allocated Memory Address.
	}

	void *Alloc(uint32_t size)
	{
		if (size > 262144)
		{
			return 0;
		}
		void *addr = 0; //Address that'll get returned.
		int iOffset = 1; //Offset in the "Free"-Area.
		int iSize = 8; //Size in Bytes, 8 is minimum.
		for (; iSize < size; iOffset++) //Get a valid size and Offset in the "Free"-Area.
		{
			iSize *= 2;
		}
		int iOrgOffset = iOffset; //Save the Offset for the optimal size.
		HeapDynFreePointer *Free = (HeapDynFreePointer *) &InitHeap->Free[0]; //Points to the "Free"-Area.
		HeapElement *Element = 0; //Will point to the Header of the entry that'll get returned.
		while (Element == 0) //As long as no element was found, search for one.
		{
			if (Free[iOffset].First == 0) //If there are no freed elements of the current size, create one.
			{
				if (InitHeap->End < ((uint64_t *)Free[0].First) + (iSize / 8) + 2) //If there is no space left, search for freed elements with larger sizes.
				{
					iOffset++;
				}
				else //There is enough space, allocate a new element.
				{
					Element = Free[0].First; //Create a new element.
					uint64_t iFirstNew = (uint64_t)Free[0].First;
					iFirstNew += sizeof(*Element) + iSize;
					Free[0].First = (HeapElement *)iFirstNew; //Set the new-element-indicator to the first address after the new element.
					Element->Size = iSize; //Put the size of the new element into the Element Header.
					addr = Element + 1; //Set the address to the address of the Element + 8B (which is sizeof(*Element)).
					return addr;
				}
			}
			else
			{
				if (Free[iOffset].First->Size > 8 * size)
				{
					//Add Heap Space

					return 0;
				}
				else
				{
					Element = Free[iOffset].First; //Set the element to the first free element.
					if (Element->Next == 0)
					{
						Free[iOffset].First = 0; //Set the first freed element entry to 0.
					}
					else
					{
						Free[iOffset].First = (HeapElement *)(Element + Element->Next); //Set the first freed element entry to the next element.
					}
					Element->Next = 0; //Set the next-entry to 0.
					addr = Element + 1; //Set the address to the address of the Element + 8B (which is sizeof(*Element)).
					return addr;
				}
			}
		}
		return 0;
	}

	void *Alloc(uint32_t size, HeapDynHeader *Header)
	{
		if (size > 262144)
		{
			return 0;
		}
		void *addr = 0; //Address that'll get returned.
		int iOffset = 1; //Offset in the "Free"-Area.
		int iSize = 8; //Size in Bytes, 8 is minimum.
		for (; iSize < size; iSize *= 2, iOffset++); //Get a valid size and Offset in the "Free"-Area.
		int iOrgOffset = iOffset; //Save the Offset for the optimal size.
		HeapDynFreePointer *Free = (HeapDynFreePointer *)&Header->Free[0]; //Points to the "Free"-Area.
		HeapElement *Element = 0; //Will point to the Header of the entry that'll get returned.
		while (Element == 0) //As long as no element was found, search for one.
		{
			if (Free[iOffset].First == 0) //If there are no freed elements of the current size, create one.
			{
				if (Header->End < ((uint64_t *)Free[0].First) + (iSize / 8) + 2) //If there is no space left, search for freed elements with larger sizes.
				{
					iOffset++;
				}
				else //There is enough space, allocate a new element.
				{
					Element = Free[0].First; //Create a new element.
					uint64_t iFirstNew = (uint64_t)Free[0].First;
					iFirstNew += sizeof(*Element) + iSize;
					Free[0].First = (HeapElement *)iFirstNew; //Set the new-element-indicator to the first address after the new element.
					Element->Size = iSize; //Put the size of the new element into the Element Header.
					addr = Element + 1; //Set the address to the address of the Element + 8B (which is sizeof(*Element)).
					return addr;
				}
			}
			else
			{
				if (Free[iOffset].First->Size > 8 * size)
				{
					//Add Heap Space

					return 0;
				}
				else
				{
					Element = Free[iOffset].First; //Set the element to the first free element.
					if (Element->Next == 0)
					{
						Free[iOffset].First = 0; //Set the first freed element entry to 0.
					}
					else
					{
						Free[iOffset].First = (HeapElement *)(Element + Element->Next); //Set the first freed element entry to the next element.
					}
					Element->Next = 0; //Set the next-entry to 0.
					addr = Element + 1; //Set the address to the address of the Element + 8B (which is sizeof(*Element)).
					return addr;
				}
			}
		}
		return 0;
	}

	void *Alloc(uint32_t size, HeapStaHeader *Header)
	{
		void *addr = 0;
		return addr;
	}

	void Free(void *addr)
	{
		if (addr == 0)
		{
			return;
		}
		HeapElement *Element = ((HeapElement *)addr) - 1;
		int iOffset = 1;
		for (uint64_t i = 8; i < Element->Size; i *= 2, iOffset++);
		HeapDynFreePointer *Free = (HeapDynFreePointer *) &InitHeap->Free[0];

		memset(addr, 0, Element->Size);

		if (Free[iOffset].First == 0)
		{
			Free[iOffset].First = Element;
		}
		else
		{
			Free[iOffset].Last->Next = (int)(Element - Free[iOffset].Last);
		}
		Free[iOffset].Last = Element;
	}

	void Free(void *addr, HeapDynHeader *Header)
	{
		if (addr == 0)
		{
			return;
		}
		HeapElement *Element = ((HeapElement *)addr) - 1;
		int iOffset = 1;
		for (uint64_t i = 8; i < Element->Size; i *= 2, iOffset++);
		HeapDynFreePointer *Free = (HeapDynFreePointer *)&Header->Free[0];

		memset(addr, 0, Element->Size);

		if (Free[iOffset].First == 0)
		{
			Free[iOffset].First = Element;
		}
		else
		{
			Free[iOffset].Last->Next = (int)(Element - Free[iOffset].Last);
		}
		Free[iOffset].Last = Element;
	}

	void Free(void *addr, HeapStaHeader *Header)
	{

	}

	void KernelCreate(uint32_t size, HeapDynHeader *Header)
	{

	}

	void KernelCreate(uint32_t size, HeapStaHeader *Header)
	{

	}
}