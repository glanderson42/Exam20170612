#ifndef CMMAP_HEADER
#define CMMAP_HEADER

#include <map>
#include <set>
#include <utility>

template<
    typename K,
    typename V,
    typename Compare = typename std::multimap<K, V>::key_compare
> class convenient_multimap : public std::multimap<K, V, Compare> {
    typedef std::multimap<K, V, Compare> container;
public:
    typedef typename container::key_type key_type;
    typedef typename container::mapped_type mapped_type;
    typedef typename container::value_type value_type;
    typedef typename container::size_type size_type;
    typedef typename container::difference_type difference_type;
    typedef typename container::key_compare key_compare;
    typedef typename container::allocator_type allocator_type;
    typedef typename container::reference reference;
    typedef typename container::const_reference const_reference;
    typedef typename container::pointer pointer;
    typedef typename container::const_pointer const_pointer;
    typedef typename container::iterator iterator;
    typedef typename container::const_iterator const_iterator;
    typedef typename container::reverse_iterator reverse_iterator;
    typedef typename container::const_reverse_iterator const_reverse_iterator;

    void add(const key_type& key, const mapped_type& value) {
        this->insert(std::make_pair(key, value));
    }

    void update_key(const key_type& old_key, const key_type& new_key) {
        container c;
        for(;;) {
            iterator it = this->find(old_key);
            if(it == this->end()) {
                break;
            }
            c.insert(*it);
            this->erase(it);
        }

        for(iterator it = c.begin(), end = c.end(); it != end; ++it) {
            this->insert(std::make_pair(new_key, it->second));
        }

    }

    template<typename UnaryFunction>
    void transform_keys(UnaryFunction fn) {
        container c;
        for(iterator it = c.begin(), end = c.end(); it != end; ++it) {
            c.insert(std::make_pair(fn(it->first), it->second));
        }
        static_cast<container&>(*this) = c;
    }
    operator std::multiset<key_type, key_compare>() const {
        std::multiset<key_type, key_compare> s;
        for(const_iterator it = this->begin(), end = this->end(); it != end; ++it) {
            s.insert(it->first);
        }
        return s;
    }

    mapped_type& front() {
        return this->begin()->second;
    }

    const mapped_type& front() const {
        return this->begin()->second;
    }

    mapped_type& back() {
        return (--this->end())->second;
    }

    const mapped_type& back() const {
        return (--this->end())->second;
    }
};

#endif
