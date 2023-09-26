# Bheap

A deceptively simple but carefully optimized lightweight binary heap that outperforms std::priority_queue and other commonly available heap implementations. Optimized for pathfinding applications with simple enregistrables types as elements.

- - - -

![picture alt](https://raw.githubusercontent.com/komrad36/Bheap/master/bheap.png "Bheap vs. std::priority_queue")

- - - -

For best results, compare entire enregistrable blocks, something like:

```cpp
struct QueueElem
{
    bool operator<(const QueueElem& other) const
    {
        U64 a, b;
        memcpy(&a, this, 8);
        memcpy(&b, &other, 8);
        return a > b;
    }
    U32 idx;
    U32 cost;
};
```
