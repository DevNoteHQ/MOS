
#include "heap.hpp"

namespace Heap
{
	HeapDynHeader *InitHeap;

	void Init()
	{
		InitHeap = (HeapDynHeader *)&_end; //Reserves Memory for Heap.
		InitHeap->Next = 0;
		HeapStackPointer *Stack = (HeapStackPointer *)&InitHeap->Stack[0];
		uint64_t HeapEnd = ((uint64_t)InitHeap) + HEAP_SIZE * 8;
		uint64_t Rest = HeapEnd % (HEAP_SIZE * 8);
		HeapEnd += (HEAP_SIZE * 8) - Rest - 1;
		uint64_t Size = HeapEnd - ((uint64_t)InitHeap) + 1;
		memset(InitHeap, 0, Size);
		InitHeap->End = (uint8_t *)HeapEnd; //Points to the end of the Heap.

		Stack[0].First = (HeapElement *)(&Stack[STACK_SIZE / 2]); //Always points to the highest, not allocated Memory Address.
	}

	void *Alloc(uint32_t size)
	{
		if (size > 262144)
		{
			return 0;
		}
		void *addr = 0; //Address that'll get returned.
		int iOffset = 1; //Offset in the "Stack".
		int iSize = 8; //Size in Bytes, 8 is minimum.
		for (; iSize < size; iOffset++) //Get a valid size and Offset in the "Stack".
		{
			iSize *= 2;
		}
		int iOrgOffset = iOffset; //Save the Offset for the optimal size.
		HeapStackPointer *Stack = (HeapStackPointer *) &InitHeap->Stack[0]; //Points to the pseudo-stack.
		HeapElement *Element = 0; //Will point to the Header of the entry that'll get returned.
		while (Element == 0) //As long as no element was found, search for one.
		{
			if (Stack[iOffset].First == 0) //If there are no freed elements of the current size, create one.
			{
				if (InitHeap->End < ((uint64_t *)Stack[0].First) + (iSize / 8) + 2) //If there is no space left, search for freed elements with larger sizes.
				{
					iOffset++;
				}
				else //There is enough space, allocate a new element.
				{
					Element = Stack[0].First; //Create a new element.
					uint64_t iFirstNew = (uint64_t)Stack[0].First;
					iFirstNew += sizeof(*Element) + iSize;
					Stack[0].First = (HeapElement *)iFirstNew; //Set the new-element-indicator to the first address after the new element.
					Element->Size = iSize; //Put the size of the new element into the Element Header.
					addr = Element + 1; //Set the address to the address of the Element + 8B (which is sizeof(*Element)).
					return addr;
				}
			}
			else
			{
				if (Stack[iOffset].First->Size > 8 * size)
				{
					//Add Heap Space

					return 0;
				}
				else
				{
					Element = Stack[iOffset].First; //Set the element to the first free element.
					if (Element->Next == 0)
					{
						Stack[iOffset].First = 0; //Set the first freed element entry to 0.
					}
					else
					{
						Stack[iOffset].First = (HeapElement *)(Element + Element->Next); //Set the first freed element entry to the next element.
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
		int iOffset = 1; //Offset in the "Stack".
		int iSize = 8; //Size in Bytes, 8 is minimum.
		for (; iSize < size; iSize *= 2, iOffset++); //Get a valid size and Offset in the "Stack".
		int iOrgOffset = iOffset; //Save the Offset for the optimal size.
		HeapStackPointer *Stack = (HeapStackPointer *)&Header->Stack[0]; //Points to the pseudo-stack.
		HeapElement *Element = 0; //Will point to the Header of the entry that'll get returned.
		while (Element == 0) //As long as no element was found, search for one.
		{
			if (Stack[iOffset].First == 0) //If there are no freed elements of the current size, create one.
			{
				if (Header->End < ((uint64_t *)Stack[0].First) + (iSize / 8) + 2) //If there is no space left, search for freed elements with larger sizes.
				{
					iOffset++;
				}
				else //There is enough space, allocate a new element.
				{
					Element = Stack[0].First; //Create a new element.
					uint64_t iFirstNew = (uint64_t)Stack[0].First;
					iFirstNew += sizeof(*Element) + iSize;
					Stack[0].First = (HeapElement *)iFirstNew; //Set the new-element-indicator to the first address after the new element.
					Element->Size = iSize; //Put the size of the new element into the Element Header.
					addr = Element + 1; //Set the address to the address of the Element + 8B (which is sizeof(*Element)).
					return addr;
				}
			}
			else
			{
				if (Stack[iOffset].First->Size > 8 * size)
				{
					//Add Heap Space

					return 0;
				}
				else
				{
					Element = Stack[iOffset].First; //Set the element to the first free element.
					if (Element->Next == 0)
					{
						Stack[iOffset].First = 0; //Set the first freed element entry to 0.
					}
					else
					{
						Stack[iOffset].First = (HeapElement *)(Element + Element->Next); //Set the first freed element entry to the next element.
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
		HeapStackPointer *Stack = (HeapStackPointer *) &InitHeap->Stack[0];

		memset(addr, 0, Element->Size);

		if (Stack[iOffset].First == 0)
		{
			Stack[iOffset].First = Element;
		}
		else
		{
			Stack[iOffset].Last->Next = (int)(Element - Stack[iOffset].Last);
		}
		Stack[iOffset].Last = Element;
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
		HeapStackPointer *Stack = (HeapStackPointer *)&Header->Stack[0];

		memset(addr, 0, Element->Size);

		if (Stack[iOffset].First == 0)
		{
			Stack[iOffset].First = Element;
		}
		else
		{
			Stack[iOffset].Last->Next = (int)(Element - Stack[iOffset].Last);
		}
		Stack[iOffset].Last = Element;
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