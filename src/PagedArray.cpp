#include "PagedArray.h"
#include <cstring>

PagedArray::PagedArray(std::ifstream& file)
    : fileStream(file), pageSize(1024 * 1024 / sizeof(int)), numPages(4), totalSize(file.seekg(0, std::ios::end).tellg() / sizeof(int)) {
    pages.resize(numPages, nullptr);
    pageLoaded.resize(numPages, false);
    fileStream.clear();
    fileStream.seekg(0, std::ios::beg);
}

int& PagedArray::operator[](size_t index) {
    size_t pageNumber = index / pageSize;
    size_t offset = index % pageSize;

    if (!pageLoaded[pageNumber % numPages]) {
        loadPage(pageNumber);
    }

    return pages[pageNumber % numPages][offset];
}

size_t PagedArray::size() const {
    return totalSize;
}

void PagedArray::loadPage(size_t pageNumber) {
    size_t pageOffset = pageNumber * pageSize * sizeof(int);
    fileStream.seekg(pageOffset);
    size_t pageIndex = pageNumber % numPages;

    if (pageLoaded[pageIndex]) {
        unloadPage(pageIndex);
    }

    pages[pageIndex] = new int[pageSize];
    fileStream.read(reinterpret_cast<char*>(pages[pageIndex]), pageSize * sizeof(int));
    pageLoaded[pageIndex] = true;
}

void PagedArray::unloadPage(size_t pageNumber) {
    delete[] pages[pageNumber];
    pages[pageNumber] = nullptr;
    pageLoaded[pageNumber] = false;
}
