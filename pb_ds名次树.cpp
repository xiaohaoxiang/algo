#include <cmath>
#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;

using order_statistic_tree = __gnu_pbds::tree<double, __gnu_pbds::null_type, less<double>, __gnu_pbds::rb_tree_tag,
                                              __gnu_pbds::tree_order_statistics_node_update>;

void multi_insert(order_statistic_tree &ost, int x);
void multi_erase(order_statistic_tree &ost, int x);

/* 洛谷P3369 */
int main()
{
    order_statistic_tree ost;
    int n, opt, x;

    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d%d", &opt, &x);
        switch (opt)
        {
        case 1: {
            multi_insert(ost, x);
            break;
        }
        case 2: {
            multi_erase(ost, x);
            break;
        }
        case 3: {
            printf("%d\n", int(ost.order_of_key(x)) + 1);
            break;
        }
        case 4: {
            printf("%d\n", int(*ost.find_by_order(x - 1)));
            break;
        }
        case 5: {
            printf("%d\n", int(*--ost.lower_bound(x)));
            break;
        }
        case 6: {
            printf("%d\n", int(*ost.lower_bound(x + 1)));
            break;
        }
        }
    }
    return 0;
}

void multi_insert(order_statistic_tree &ost, int x)
{
    auto it = ost.lower_bound(x + 1);
    if (it == ost.begin())
    {
        ost.insert(x);
    }
    else
    {
        --it;
        if (int(*it) == x)
        {
            ost.insert(nextafter(*it, *it + 1));
        }
        else
        {
            ost.insert(x);
        }
    }
}

void multi_erase(order_statistic_tree &ost, int x)
{
    ost.erase(--ost.lower_bound(x + 1));
}