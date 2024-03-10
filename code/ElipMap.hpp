#ifndef H__ELIP__MAP__H
#define H__ELIP__MAP__H
#include <map>
#include "ElipVector.hpp"
#include "ElipString.hpp"
#include "ElipExceptions.hpp"
#include "ElipFormat.hpp"
#include <vector>
namespace Elip
{
    template <typename K, typename V>

    class Map
    {
    private:
        Elip::Vector<K> _keys;
        Elip::Vector<V> _values;

    public:
        Map()
        {
        }

        bool Exists(K key)
        {
            if (this->_keys.Search(key) == -1)
            {
                return false;
            }
            return true;
        }
        void Delete(K key)
        {
            if (this->_keys.Search(key) == -1)
            {
                throw Elip::MapKeyError("The key not exist");
            }
            else
            {
                auto index = this->_keys.Search(key);
                this->_keys.Delete(index);
                this->_values.Delete(index);
            }
        }
        void Set(K key, V value)
        {
            if (this->_keys.Search(key) == -1)
            {
                this->_keys.PushBack(key);
                this->_values.PushBack(value);
            }
            else
            {
                auto index = this->_keys.Search(key);

                this->_values.Set(index, value);
            }
        }
        V Get(K key)
        {
            if (this->_keys.Search(key) == -1)
            {
                throw Elip::MapKeyError("The key not exist");
            }
            else
            {
                return this->_values.Get(this->_keys.Search(key));
            }
        }
        /*
        {hola:20,}
        */

        std::size_t GetSize()
        {
            return this->_keys.GetSize();
        }
        std::size_t GetLength()
        {
            return this->GetSize();
        }
        Elip::String ToString()
        {
            Elip::Vector<K> keys = this->GetKeys();
            Elip::Vector<V> values = this->GetValues();
            Elip::String str;
            str.ReserveMemory(sizeof(V) + sizeof(K) * keys.GetSize() + sizeof("{") + sizeof("}") + (sizeof(":") * keys.GetSize() - 1));
            str.InsertRight("{");
            for (std::size_t i = 0; i < keys.GetSize(); i++)
            {
                if (i + 1 < keys.GetSize())
                {
                    str.InsertRight(Elip::FormatWithoutColor("{}:{},", keys[i], values[i]).ToString());
                }
                else
                {
                    str.InsertRight(Elip::FormatWithoutColor("{}:{}", keys[i], values[i]).ToString());
                }
            }
            str.InsertRight("}");
            return str;
        }
        Elip::Vector<K> GetKeys()
        {
            return this->_keys.Copy();
        }
        Elip::Vector<V> GetValues()
        {
            return this->_values.Copy();
        }
    };
}; // namespace Elip

#endif