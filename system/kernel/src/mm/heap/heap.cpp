
#include "heap.hpp"

namespace Heap
{
	HeapDynHeader *InitHeap;

	void *Alloc(uint64_t size)
	{
		void *addr = 0; //Address that'll get returned.
		int iOffset = 1; //Offset in the "Stack".
		int iSize = 16; //Size in Bytes, 16 is minimum.
		for (; iSize < size; iSize *= 2, iOffset++); //Get a valid size and Offset in the "Stack".
		int iOrgOffset = iOffset; //Save the Offset for the optimal size.
		HeapStackPointer *Stack = InitHeap->Stack; //Points to the pseudo-stack.
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
				}
			}
			else
			{
				Element = Stack[iOffset].First; //Set the element to the first free element.
				Stack[iOffset].First = Element->Next; //Set the first free element entry to the next element (even if the next element is zero).
				if (Element->Size > size * 2)
				{
					//Split Elements.
				}
				Element->Next = 0; //Set the next-entry to 0.
			}
		}
		addr = Element + 1; //Set the address to the address of the Element + 16B (which is sizeof(*Element)).
		return addr;
	}

	void *Alloc(uint64_t size, HeapDynHeader *Header)
	{
		void *addr = 0;
		return addr;
	}

	void *Alloc(uint64_t size, HeapStaHeader *Header)
	{
		void *addr = 0;
		return addr;
	}

	void Free(void *addr)
	{
		HeapElement *Element = ((HeapElement *)addr) - 1;
		int iOffset = 1;
		for (uint64_t i = 16; i < Element->Size; i *= 2, iOffset++);
		HeapStackPointer *Stack = InitHeap->Stack;

		memset(addr, 0, Element->Size);

		if (Stack[iOffset].First == 0)
		{
			Stack[iOffset].First = Element;
		}
		else
		{
			Stack[iOffset].Last->Next = Element;
		}
		Stack[iOffset].Last = Element;
	}

	void Free(void *addr, HeapDynHeader *Header)
	{

	}

	void Free(void *addr, HeapStaHeader *Header)
	{

	}
}