/*
 * Copyright (c) 2026 Amber-Sophia Schröck. Licensed under the EUPL, Version 1.2 or as soon they will be approved by the
 * European Commission - subsequent versions of the EUPL (the "Licence"); You may not use this work except in compliance
 * with the Licence. You may obtain a copy of the Licence at: http://joinup.ec.europa.eu/software/page/eupl Unless
 * required by applicable law or agreed to in writing, software distributed under the Licence is distributed on an
 * "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the Licence for the
 * specific language governing permissions and limitations under the Licence.
 */
#ifndef __UT_RECTANGLE_H__
#define __UT_RECTANGLE_H__

#include "utconfig.h"
#include "utvector2.h"

namespace utb {
    namespace math {
        template <typename T>
        class rectangle {
        public:
            using value_type = T;
            using self_type = rectangle<T>;
            using pointer = T* ;
            
            union {
                struct {
                    value_type x;
                    value_type y;
                    value_type width;
                    value_type height;
                };
                struct {
                    vector2<T> position;
                    vector2<T> size;
                };
                value_type c[4];
            };

            rectangle() 
                : x(0), y(0), width(1), height(1) { }
            rectangle(value_type _x, value_type _y, value_type _w, value_type _h) 
                : x(_x), y(_y), width(_w), height(_h) { }

            rectangle(vector2<value_type> pos, vector2<value_type> size) 
                : x(pos.x), y(pos.y), width(size.x), height(size.y) { }

            rectangle(const rectangle& rect) 
                : x(rect.x), y(rect.y), width(rect.width), height(rect.height) { }
            rectangle(rectangle&& rect) noexcept
                : x(utb::move(rect.x)), y(utb::move(rect.y)), width(utb::move(rect.width)), height(utb::move(rect.height)) { }

            
            const value_type& top() { return y; }
            void top(const value_type& t) { y = t; }
            
            const value_type& left() { return x; }
            void left(const value_type& t) { x = t; }
            
            const value_type& bottom() { return y + height; }
            const value_type& right() { return x + width; }
            
            vector2<value_type> center() { return vector2<T>(x + width / 2, y + height / 2); }
            vector2<value_type> size() { return vector2<value_type>(width, height); }
            
            rectangle<value_type> inflate (value_type leftRight, value_type topBottom) {
	            x -= leftRight;
                width += leftRight * 2;
                y -= topBottom;
                height += topBottom * 2;

                return *this;
            }
            bool contains(self_type r) {
               return r.left() >= left() && r.right() <= right() &&
                       r.top() >= top() && r.bottom() <= bottom();
            }
            self_type& intersect(const self_type& r1, const self_type& r2)  {
                int x = utb::max<value_type> (r1.x, r2.x);
                int y = utb::max<value_type> (r1.y, r2.y);
                int w = utb::min<value_type> (r1.right(), r2.right()) - x;
                int h = utb::min<value_type> (r1.bottom(), r2.bottom()) - y;

                return self_type(x,y,w,h);
            }
            bool intersects(const self_type& r) {
                int w = utb::min<value_type> (r.right(), right()) - utb::max<value_type> (r.x, x);
		        int h = utb::min<value_type> (r.bottom(), bottom()) - utb::max<value_type> (r.y, y);
		        return w > 0 && h > 0;
            }
            void offset(float offx, float offy) {
                x += offx;
                y += offy;
            }

            bool operator == (const self_type& r) const {
                return (x == r.x) && (y == r.y) && (width == r.width) && (height == r.height);
            }
            bool operator != (const self_type& r) const {
                return !(*this == r);
            }
            bool is_valid() const {
                return (width > 0) && (height > 0);
            }
            pointer operator pointer ()		{ return (pointer)(c); }

            self_type& copy() {
                return self_type(x, y, width, height);
            }
            self_type& swap(self_type& other) noexcept {
                if (this != &other) {
                    utb::swap(x, other.x);
                    utb::swap(y, other.y);
                    utb::swap(width, other.width);
                    utb::swap(height, other.height);
                }
                return *this;
            }
            self_type& scale(int scale) {
                value_type nx = x * scale;
                value_type ny = y * scale;
                value_type nwidth = width * scale;
                value_type nheight = height * scale;
                return self_type(nx, ny, nwidth, nheight);
            }
            self_type& scale(int scalex, int scaley) {
                value_type nx = x * scalex;
                value_type ny = y * scaley;
                value_type nwidth = width * scalex;
                value_type nheight = height * scaley;
                return self_type(nx, ny, nwidth, nheight);
            }
            
            self_type& scale(float scale) {
                value_type nx = static_cast<value_type>(x * scale);
                value_type ny = static_cast<value_type>(y * scale);
                value_type nwidth = static_cast<value_type>(width * scale);
                value_type nheight = static_cast<value_type>(height * scale);
                return self_type(nx, ny, nwidth, nheight);
            }
            self_type& scale(float scalex, float scaley) {
                value_type nx = static_cast<value_type>(x * scalex);
                value_type ny = static_cast<value_type>(y * scaley);
                value_type nwidth = static_cast<value_type>(width * scalex);
                value_type nheight = static_cast<value_type>(height * scaley);
                return self_type(nx, ny, nwidth, nheight);
            }
        };


        
    }
}

#endif