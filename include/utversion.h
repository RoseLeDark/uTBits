/*
 * Copyright (c) 2026 Amber-Sophia Schröck. Licensed under the EUPL, Version 1.2 or as soon they will be approved by the
 * European Commission - subsequent versions of the EUPL (the "Licence"); You may not use this work except in compliance
 * with the Licence. You may obtain a copy of the Licence at: http://joinup.ec.europa.eu/software/page/eupl Unless
 * required by applicable law or agreed to in writing, software distributed under the Licence is distributed on an
 * "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the Licence for the
 * specific language governing permissions and limitations under the Licence.
 */
#ifndef __UT_VERSION_H__
#define __UT_VERSION_h__

#define UTB_CONCAT2(X, Y)  X##Y
#define UTB_CONCAT(X, Y)   UTB_CONCAT2(X, Y)

#define UTB_STRINGIFY_1(...) #__VA_ARGS__
#define UTB_STRINGIFY(...) UTB_STRINGIFY_1(__VA_ARGS__)

#define UTB_STRING(X)      UTB_CONCAT(, UTB_STRINGIFY(X))

#define UTB_VERSION_MAJOR   1
#define UTB_VERSION_MINOR   8
#define UTB_VERSION_PATCH   6
#define UTB_VERSION_PREFIX  -beta

#define UTB_VERSION_STRING       UTB_STRING(UTB_VERSION_MAJOR) "." UTB_STRING(UTB_VERSION_MINOR) "." UTB_STRING(UTB_VERSION_PATCH)  UTB_STRING(UTB_VERSION_PREFIX)


namespace utb
{
  namespace traits
  {
    static constexpr unsigned char version_major             = UTB_VERSION_MAJOR;
    static constexpr unsigned char version_minor             = UTB_VERSION_MINOR;
    static constexpr unsigned char version_patch             = UTB_VERSION_PATCH;

    static constexpr const char* version_string        = UTB_VERSION_STRING;

  }
}

#endif