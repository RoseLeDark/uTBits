/*
 * Copyright (c) 2026 Amber-Sophia Schröck. Licensed under the EUPL, Version 1.2 or as soon they will be approved by the
 * European Commission - subsequent versions of the EUPL (the "Licence"); You may not use this work except in compliance
 * with the Licence. You may obtain a copy of the Licence at: http://joinup.ec.europa.eu/software/page/eupl Unless
 * required by applicable law or agreed to in writing, software distributed under the Licence is distributed on an
 * "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the Licence for the
 * specific language governing permissions and limitations under the Licence.
 */
#ifndef __UTBHASH_H__
#define __UTBHASH_H__

#include "utconfig.h"
#include <cstdint>
#include <string.h>

namespace utb {
    using hash_type = utb::size_t;


	namespace internal {

        #define ROTL32(x, r) (uint32_t) ( (x << r) | (x >> (32 - r)) );

        uint32_t mmh3_x86(const void* key, int len, uint32_t seed) {
            const uint8_t * data = (const uint8_t*)key;
            const int nBlocks = len / 4;
            const uint32_t * blocks = (const uint32_t *)(data + nBlocks*4);

            uint32_t hash = seed;

            const uint32_t c1 = 0xcc9e2d51;
            const uint32_t c2 = 0x1b873593;

            uint32_t k;
            for (int i = 0; i < nBlocks ; ++i) {
                k = blocks[i];
                
                k *= c1;
                k = ROTL32(k,15);
                k *= c2;
                
                hash ^= k;
                hash = ROTL32(hash, 13);
                hash = (hash * 5) + 0xe6546b64;
            }
            
            const uint8_t * tail = (const uint8_t*)(data + nBlocks*4);

            uint32_t k1 = 0;

            switch(len & 3) {
                case 3: 
                    k ^= tail[2] << 16;
                case 2: 
                    k ^= tail[1] << 8;
                case 1: 
                    k ^= tail[0];
                    k *= c1;
                    k = ROTL32(k,15);
                    k *= c2;
                    hash ^= k;
            }
            
            hash ^= len;
            hash ^= hash >> 16;
            hash *= 0x85ebca6b;
            hash ^= hash >> 13;
            hash *= 0xc2b2ae35;
            hash ^= hash  >> 16;
                    
            return hash;
        }


      }
	/**
	 * @brief Default implementation of hasher.
	 */
	template<typename T>
	struct hash {
		const hash_type operator()(T& t) const noexcept {
			return (hash_type) internal::mmh3_x86(&t, strlen( (char*)&t), UTB_CONFIG_BASIC_HASHMUL_VAL);
		}
	};

	template<typename T>
    struct hash<T*>{
		hash_type operator () (T* pPtr) const noexcept {
			assert(pPtr);

			return (hash_type) internal::mmh3_x86(&pPtr, strlen((char *)pPtr), UTB_CONFIG_BASIC_HASHMUL_VAL);
		}
    };

  	template<>
    struct hash<char*>{
		const hash_type operator()(const char* t) const noexcept {
			return (hash_type) internal::mmh3_x86(t, strlen(t), UTB_CONFIG_BASIC_HASHMUL_VAL);
		}
    };

    template<>
    struct hash<const char*>{
		const hash_type operator()(const char* t) const noexcept {
			return (hash_type) internal::mmh3_x86(t, strlen(t), UTB_CONFIG_BASIC_HASHMUL_VAL);
		}
    };

    template<>
    struct hash<int8_t>{
		hash_type operator () (int8_t n) const noexcept {
			return static_cast<hash_type>(n) * UTB_CONFIG_BASIC_HASHMUL_VAL;
		}
    };


	template<>
    struct hash<uint8_t>{
		hash_type operator () (uint8_t n) const noexcept {
			return static_cast<hash_type>(n) * UTB_CONFIG_BASIC_HASHMUL_VAL;
		}
    };


	template<>
    struct hash<int16_t>{
		hash_type operator () (int16_t n) const noexcept {
			return static_cast<hash_type>(n) * UTB_CONFIG_BASIC_HASHMUL_VAL;
		}
    };

	template<>
    struct hash<uint16_t>{
		hash_type operator () (uint16_t n) const noexcept {
			return static_cast<hash_type>(n) * UTB_CONFIG_BASIC_HASHMUL_VAL;
		}
    };

	template<>
    struct hash<int32_t>{
		hash_type operator () (int32_t n) const noexcept {
			return static_cast<hash_type>(n) * UTB_CONFIG_BASIC_HASHMUL_VAL;
		}
    };

	template<>
    struct hash<uint32_t>{
		hash_type operator () (uint32_t n) const noexcept {
			return static_cast<hash_type>(n) * UTB_CONFIG_BASIC_HASHMUL_VAL;
		}
    };


	template<>
    struct hash<int64_t>{
		hash_type operator () (int64_t n) const noexcept {
			return static_cast<hash_type>(n) * UTB_CONFIG_BASIC_HASHMUL_VAL;
		}
    };


	template<>
    struct hash<uint64_t>{
		hash_type operator () (const uint64_t n) const noexcept {
			return static_cast<hash_type>(n) * UTB_CONFIG_BASIC_HASHMUL_VAL;
		}
    };

    template <class T>
	struct hash_function {
		hash_type operator () (T key, size_t maxValue) const noexcept {
			return utb::hash<T>{}(key) % maxValue;
		}
	};


	template <>
	struct hash_function<const char*> {
		hash_type operator () (const char* key, size_t maxValue) const noexcept {
			return (hash_type) internal::mmh3_x86(key, strlen(key), UTB_CONFIG_BASIC_HASHMUL_VAL);
		}
	};
}

#endif // __UTBHASH_H__