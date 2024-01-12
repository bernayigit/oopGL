#pragma once

#include "object.hpp"

namespace ogl
{
    class IndexedObject : public Object
    {
        protected:
            static std::shared_ptr<Buffer> EBO;
    };
}