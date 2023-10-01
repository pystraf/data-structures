template<typename T, typename Compare = std::less<T>>
class Heap {
private:
	size_t heap_size, heap_capa;
	T* heap;
	Compare comp;

	// Allocate heap
	void init(size_t c) {
		heap = new T[c + 1];
		heap_capa = c;
	}

	// Deallocate heap
	void free() {
		delete[] heap;
		heap = NULL;
		heap_capa = 0;
	}

	// Sift up
	void up(size_t i) {
		size_t parent = i / 2;
		if (parent >= 1 && comp(heap[i], heap[parent])) {
			swap(heap[i], heap[parent]);
			up(parent);
		}
	}

	// Sift down
	void down(size_t i) {
		size_t l = i * 2, r = l + 1;
		size_t u = i;
		if (l <= n && comp(heap[l], heap[u])) u = l;
		if (r <= n && comp(heap[r], heap[u])) u = r;
		if (u != i) {
			swap(heap[u], heap[i]);
			down(u);
		}
	}
public:
	// Constructor
	Heap(size_t capacity, Compare comp = Compare()) comp(comp){
		init(capacity);
	}
	// Destructor
	~Heap() {
		free();
	}
	// Push x into heap
	bool push(T x) {
		if (heap_size >= heap_capa) return false;
		heap[++heap_size] = x;
		down(heap_size);
		up(heap_size);
		return true;
	}

	// Get top element
	T top() {
		return heap[1];
	}

	// Pop top element
	bool pop() {
		if (heap_size) {
			heap[1] = heap[heap_size--];
			down(1);
            return true;
		}
        return false;
	}

	// Set top element
	void set_top(T x) {
		heap[1] = x;
		down(1);
	}
};
