#include <queue>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    long long value; // n = base^k
    int k;           // power
    int base;
    bool operator>(const Node& other) const {
        return value > other.value;
    }
};

priority_queue<Node, vector<Node>, greater<Node>> CreateHeap(long long m) {
    priority_queue<Node, vector<Node>, greater<Node>> heap;
    long long limit = sqrt((long double)m) + 1;
    for (int base = 2; base <= limit; ++base) {
        heap.push({ (long long)base * base, 2, base });
    }
    return heap;
}

Node PopUntilM(priority_queue<Node, vector<Node>, greater<Node>>& heap, long long m) {
    Node best = { -1, 0, 0 };
    if (heap.empty()) return best;

    // We pop until top >= m
    while (!heap.empty() && heap.top().value < m) {
        Node cur = heap.top();
        heap.pop();
        best = cur; // last < m

        // push next power: base^(k+1) - without m/base trick as you wanted
        if (cur.value <= LLONG_MAX / cur.base) { // only overflow guard
            heap.push({ cur.value * cur.base, cur.k + 1, cur.base });
        }
    }

    if (!heap.empty()) return heap.top(); // first >= m
    return best; // if no >= m found, return greatest < m
}

int GreatestKth(const long long m) {
    auto heap = CreateHeap(m);
    Node result = { -1, 0, 0 };
    if (!heap.empty()) {
        result = PopUntilM(heap, m);
    }
    return (int)result.value;
}

int main() {
    long long m;
    cin >> m;
    cout << GreatestKth(m) << endl;
    return 0;
}
//#include<queue>
//#include<cmath>
//#include<iostream>
//#include<vector>
//#include<algorithm>
//using namespace std;
//
//struct Node {
//	long long value; // n = base^k
//	int k;           // power
//	int base;
//	bool operator>(const Node& other) const {
//		return value > other.value;
//	}
//};
//
//priority_queue<Node, vector<Node>, greater<Node>> CreateHeap(long long m) {
//	priority_queue<Node, vector<Node>, greater<Node>> heap;
//	long long limit = sqrt(m) + 1;
//	for (int base = 2; base <= limit; ++base) {
//		heap.push({ (long long)base * base, 2, base });
//	}
//	return heap;
//}
//Node PopUntilM(priority_queue<Node, vector<Node>, greater<Node>>& heap, long long m) {
//	Node best = { -1, 0, 0 };
//	if (heap.empty()) return best;
//
//	while (!heap.empty() && heap.top().value < m) {
//		Node cur = heap.top();
//		heap.pop();
//		best = cur; // this is last valid < m
//
//		// push next power of same base: base^(k+1)
//		// check overflow: cur.value * cur.base <= m maybe + some limit
//		if (cur.value <= m) { // avoid overflow
//			heap.push({ cur.value * cur.base, cur.k + 1, cur.base });
//		}
//	}
//	return best;
//}
////Node pop(priority_queue<Node, vector<Node>, greater<Node>>& heap, const int m) {
////	Node result = {-1,0,0};
////	if(heap.empty()) return {-1, -1, -1};
////	result = heap.top();
////	while (!heap.empty() && result.value < m) {
////		heap.pop();
////		result = heap.top();
////	}
////	return result;
////}
//int GreatestKth(const int m) {
//	
//	priority_queue<Node, vector<Node>, greater<Node>> heap;
//	heap = CreateHeap(m);
//	Node result = { -1, 0, 0 };
//	if (!heap.empty()) {
//		result = PopUntilM(heap, m);
//	}
//	 
//	// No need for m/2, sqrt(m)+1 is enough!
//	//int counts = sqrt(m) + 1;
//	//vector<long long> results;
//
//	//for (int base = 2; base <= counts; ++base) {
//	//	long long result = 1LL * base * base;
//	//	while (result < m) result *= base; // *= base, not * result
//	//	results.push_back(result);
//	//}
//	//sort(results.begin(), results.end());
//	//for (auto v : results) if (v >= m) return (int)v;
//	//return -1;
//	return result.value;
//}
//int main() {
//	int m;
//	cin >> m;
//	cout << GreatestKth(m) << endl;
//	return 0;
//}
//
//void CreateHeap(std::vector<Node>& heap, int k, int base) {
//    heap.clear();
//    long long value = 1;
//    for (int i = 0; i <= k; ++i) {
//        heap.push_back({ value, i, base });
//        value *= base;
//    }
//    std::make_heap(heap.begin(), heap.end(), std::greater<Node>());
//}