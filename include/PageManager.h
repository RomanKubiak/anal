#ifndef page_manager_
#define page_manager_

#include "Page.h"
#define MAX_PAGES 16
class AnalPageManager
{
	public:
		AnalPageManager(ILI9341_t3 &_g);
		void update();
		void begin();
		void addPage(AnalPage *page);
	private:
		ILI9341_t3 &g;
		AnalPage *pages[MAX_PAGES];
		uint8_t pageCount;
		uint8_t currentPage;
};

#endif