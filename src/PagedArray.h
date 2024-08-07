#ifndef PAGEDARRAY_H
#define PAGEDARRAY_H

#include <fstream>
#include <vector>

class PagedArray {
public:
    PagedArray(std::ifstream& file);
    int& operator[](size_t index);
    size_t size() const;

private:
    void loadPage(size_t pageNumber);
    void unloadPage(size_t pageNumber);

    std::ifstream& fileStream;
    std::vector<int*> pages;
    std::vector<bool> pageLoaded;
    size_t pageSize;
    size_t numPages;
    size_t totalSize;
};

#endif // PAGEDARRAY_H
