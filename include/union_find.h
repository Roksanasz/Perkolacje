#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <vector>
#include <numeric>
#include <stdexcept>

using Punkt = std::pair<int, int>;

class UnionFind
{
  public:
    UnionFind(int size)  //
        : next(size), rank(size)
    {
        if (size < 0 || size > 100000000)
            throw std::invalid_argument("invalid 'size' in UnionFind: " + std::to_string(size));
        // początkowo każdy rekord danych to samodzielny zbiór
        // next = {0, 1, 2,...}; czyli next[i] = i, czyli każdy element pokazuje samego siebie
        std::iota(next.begin(), next.end(), 0); //Fills the range [first, last) with sequentially increasing values
    }

    size_t set_find(size_t i)
    {
        auto root = i;
        while (next[root] != root)
        {
            root = next[root];
        }
        // teraz skracamy drzewo
        auto ni = next[i];
        while (ni != root)
        {
            next[i] = root;
            i = ni;
            ni = next[ni];
        }
        return root;
    }
    void set_union(size_t i, size_t j)
    {
        const auto root_i = set_find(i);
        const auto root_j = set_find(j);
        if (root_i == root_j)
        {
            return;
        }
        if (rank[root_i] < rank[root_j])
        {
            next[root_i] = root_j;
        }
        else
        {
            next[root_j] = root_i;
            if (rank[root_i] == rank[root_j])
            {
                rank[root_i]++;
            }
        }
    }
    size_t get_rank(size_t n) const { return rank[n]; }
    size_t size() const { return rank.size(); }

  private:
    std::vector<size_t> next;
    std::vector<int> rank;
};
#endif  // UNION_FIND_H
