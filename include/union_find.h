#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <vector>
#include <numeric>
#include <stdexcept>
#include <vector>

using Punkt = std::pair<int, int>;

class UnionFind
{
  public:
    UnionFind(int size,                                            //
              const std::vector<unsigned>& horizontal_nodes = {},  // numery węzłów na krawędzi poziomej
              const std::vector<unsigned>& vertical_nodes = {},    // numery węzłów na krawędzi pionowej
              const std::vector<unsigned>& diagonal_nodes = {})    // numery węzłów na krawędzi ukośnej
        : next(size), rank(size)
    {
        if (size < 0 || size > 100000000)
            throw std::invalid_argument("invalid 'size' in UnionFind: " + std::to_string(size));
        // początkowo każdy rekord danych to samodzielny zbiór
        // next = {0, 1, 2,...}; czyli next[i] = i, czyli każdy element pokazuje samego siebie
        std::iota(next.begin(), next.end(), 0);
    }
    ~UnionFind() = default;

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
            connected_to_diagonal[root_j] = connected_to_diagonal[root_j] || connected_to_diagonal[root_i];
            connected_to_horizontal[root_j] = connected_to_horizontal[root_j] || connected_to_horizontal[root_i];
            connected_to_vertical[root_j] = connected_to_vertical[root_j] || connected_to_vertical[root_i];
        }

        else
        {
            next[root_j] = root_i;
            if (rank[root_i] == rank[root_j])
            {
                rank[root_i]++;
            }
            connected_to_diagonal[root_i] = connected_to_diagonal[root_j] || connected_to_diagonal[root_i];
            connected_to_horizontal[root_i] = connected_to_horizontal[root_j] || connected_to_horizontal[root_i];
            connected_to_vertical[root_i] = connected_to_vertical[root_j] || connected_to_vertical[root_i];
        }
    }
    size_t get_rank(size_t n) const { return rank[n]; }
    size_t size() const { return rank.size(); }
    bool spans_3_sides(int numer_wezla) const
    {

        return connected_to_diagonal[numer_wezla] &&connected_to_horizontal[numer_wezla]&&connected_to_vertical[numer_wezla];
    }

  private:
    std::vector<int> next;
    std::vector<int> rank;
    std::vector<bool> connected_to_horizontal;
    std::vector<bool> connected_to_vertical;
    std::vector<bool> connected_to_diagonal;
};
#endif  // UNION_FIND_H
