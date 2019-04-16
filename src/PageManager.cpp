#include "PageManager.h"

AnalPageManager::AnalPageManager(ILI9341_t3 &_g)
	: g(_g), pageCount(0), currentPage(0)
{
	for (int i=0; i<MAX_PAGES; i++)
	{
		pages[i] = nullptr;
	}
}

void AnalPageManager::begin()
{
}

void AnalPageManager::update()
{
	if (pages[currentPage])
	{
		pages[currentPage]->update();
	}
}

void AnalPageManager::addPage(AnalPage *page)
{
	for (int i=0; i<MAX_PAGES; i++)
	{
		if (pages[i] == nullptr)
		{
			pages[i] = page;
			pageCount++;
			return;
		}
	}
}