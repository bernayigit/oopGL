namespace ogl
{
    Renderer::Renderer()
    {
    }

    /**
     * Since we're binding the VAO, this function should work for
     * both Objects and IndexedObjects.
    */
    Renderer& Renderer::operator<<(const Object& object)
    {
        if(object.getVertexArray().getId() != last_used_VAO)
        {
            glBindVertexArray(0);
            
            object.getVertexArray().bind();
            
            last_used_VAO = object.getVertexArray().getId(); 
        }

        object.draw();

        return *this;
    }

    bool Renderer::addVertexShader(const VertexShader &shader, const std::string &name)
    {
        if(vertex_shaders.contains(name))
        {
            return false;
        } else 
        {
            vertex_shaders[name] = shader;

            return true;
        }
    }

    bool Renderer::removeVertexShader(const std::string &name)
    {
        if(!vertex_shaders.contains(name))
        {
            return false;
        } else 
        {
            vertex_shaders.erase(name);

            return true;
        }
    }

    #ifdef GEOM_SHADER
    bool Renderer::addGeometryShader(const GeometryShader &shader, const std::string &name)
    {
    }
    
    bool Renderer::removeGeometryShader(const std::string &name)
    {
    }
    #endif

    bool Renderer::addFragmentShader(const FragmentShader &shader, const std::string &name)
    {
        if(fragment_shaders.contains(name))
        {
            return false;
        } else 
        {
            fragment_shaders[name] = shader;

            return true;
        }
    }
    
    bool Renderer::removeFragmentShader(const std::string &name)
    {
        if(!fragment_shaders.contains(name))
        {
            return false;
        } else 
        {
            fragment_shaders.erase(name);

            return true;
        }
    }

    bool Renderer::useVertexShader(const std::string& name)
    {
        if(vertex_shaders.contains(name))
        {
            vertex_shaders[name].use();

            active_shaders.vertex_shader = name;

            return true;
        } else 
        {
            return false;
        }
    }

    bool Renderer::useFragmentShader(const std::string& name)
    {
        if(fragment_shaders.contains(name))
        {
            fragment_shaders[name].use();

            active_shaders.fragment_shader = name;

            return true;
        } else 
        {
            return false;
        }
    }

    VertexShader& Renderer::getActiveVertexShader() 
    {
        return vertex_shaders[active_shaders.vertex_shader];
    }

    FragmentShader& Renderer::getActiveFragmentShader() 
    {
        return fragment_shaders[active_shaders.fragment_shader];
    }

    VertexShader& Renderer::getVertexShader(const std::string& name)
    {
        return vertex_shaders[name];
    }

    FragmentShader& Renderer::getFragmentShader(const std::string& name)
    {
        return fragment_shaders[name];
    }
}