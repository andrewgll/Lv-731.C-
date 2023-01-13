// by Klepatskyi Oleh
#ifndef _KLEPATSKYI_CONCURRENT_UNORDERED_MAP_H_
#define _KLEPATSKYI_CONCURRENT_UNORDERED_MAP_H_

#include <mutex>
#include <unordered_map>

template<class K, class V>
class ConcurrentUnorderedMap {
private:
	std::unordered_map<K, V> _map;
	mutable std::mutex _mutex;
public:
	ConcurrentUnorderedMap() = default;
	ConcurrentUnorderedMap(const ConcurrentUnorderedMap&) = delete;
	ConcurrentUnorderedMap& operator=(const ConcurrentUnorderedMap&) = delete;

	inline void insert(const K& key, const V& value)
	{
		std::lock_guard<std::mutex> lg(_mutex);
		_map.insert({ key, value });
	}

	inline const V& at(const K& key) const
	{
		std::lock_guard<std::mutex> lg(_mutex);
		return _map.at(key);
	}

};

#endif // _KLEPATSKYI_CONCURRENT_UNORDERED_MAP_H_
