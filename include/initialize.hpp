#pragma once

#include "GL/glew.h"

namespace ogl::details
{
    class Initialize
    {
        public:
            Initialize()
            {
                if(counter++ == 0)
                {
                    glewInit();
                }
            }
        
        private:
            static size_t counter;
    };

    static Initialize initialize;
}