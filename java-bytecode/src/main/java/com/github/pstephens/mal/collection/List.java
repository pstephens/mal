package com.github.pstephens.mal.collection;

public class List<T> {
    private static final List emptyList = new List();

    private final T head;

    private final List<T> tail;

    private List(T head, List<T> tail) {
        this.head = head;
        this.tail = tail;
    }

    private List() {
        this(null, null);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        boolean first = true;
        sb.append("(");
        List<T> cur = this;
        while(cur != emptyList) {
            if(first) {
                first = false;
            } else {
                sb.append(", ");
            }

            sb.append(cur.head());
            cur = cur.tail();
        }

        sb.append(")");
        return sb.toString();
    }

    public boolean isEmpty() { return this == emptyList; }

    public List<T> tail() {
        if(this == emptyList) {
            throw new UnsupportedOperationException("Empty list");
        } else {
            return tail;
        }
    }

    public T head() {
        if(this == emptyList) {
            throw new UnsupportedOperationException("Empty list");
        } else {
            return head;
        }
    }

    @SuppressWarnings("unchecked")
    public static <T> List<T> empty() {
        return (List<T>)emptyList;
    }

    @SafeVarargs
    public static <T> List<T> create(T item1, T item2, T item3, T... moreItems) {
        List<T> list = List.empty();
        int index = moreItems.length - 1;
        while(index >= 0) {
            list = list.cons(moreItems[index]);
            --index;
        }

        return list.cons(item3).cons(item2).cons(item1);
    }

    public static <T> List<T> create(T item1) {
        return List.<T>empty().cons(item1);
    }

    public static <T> List<T> create(T item1, T item2) {
        return List.<T>empty().cons(item2).cons(item1);
    }


    public static <T> List<T> create(T item1, T item2, T item3) {
        return List.<T>empty().cons(item3).cons(item2).cons(item1);
    }

    public List<T> cons(T element) { return new List<>(element, this); }

    public List<T> reverse() {
        List<T> result = empty();
        List<T> cur = this;
        while(cur != emptyList) {
            result = result.cons(cur.head());
            cur = cur.tail();
        }

        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if(obj == this)
            return true;
        if(obj == null)
            return false;
        if(!(obj instanceof List))
            return false;

        List<?> cur1 = this;
        List<?> cur2 = (List) obj;

        while(true) {
            if(cur1 == emptyList) {
                return cur2 == emptyList;
            }
            else if(cur2 == emptyList) {
                return false;
            }
            else if(cur1.head() == null) {
                if(cur2.head() != null) {
                    return false;
                }
            } else if(!cur1.head().equals(cur2.head())) {
                return false;
            }

            cur1 = cur1.tail();
            cur2 = cur2.tail();
        }
    }

    @Override
    public int hashCode() {
        List<T> cur = this;
        int acc = 0;
        while(cur != emptyList) {
            acc *= 37;
            if(cur.head() != null) {
                acc += cur.head().hashCode();
            } else {
                acc += 17;
            }

            cur = cur.tail();
        }

        return acc;
    }
}
