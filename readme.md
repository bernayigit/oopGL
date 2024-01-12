VertexBuffer
{
    Construct();

    bool setData(span<bytes>)
    bool setData(size_t inizio, span<bytes>)

    VertexBuffer operator+=(VertexAttributes)

    void upload()

    GLuint getId()

    vector<byte> data
}

VertexAttributes
{
    Construct()

    struct Attribute
    {
        GLenum       data_type;
        vector<byte> data;
    }

    span<T> getAttribute(size_t index)
    void     setAttribute(size_t index, span<T>, GLenum type)
    void     removeAttributes(size_t index)

    bool hasChanged()
    
    size_t getSize()

    span<byte> getData()

    unordered_map<size_t, Attribute> attributes
    vector<byte>      data  // if any functions changes attribs,
                            // recalculate data
}

SAME BUFFER 
{
    DYNAMIC_BUFFER, STATIC_BUFFER_POOL
}

OWN BUFFER
{
    DYNAMIC, STATIC
}

Object
{
    virtual draw()

    VertexAttributes vertex_attributes;

    virtual void loadAttributes();

    static VAO;
}

object has Buffer shared pointer
object has OFFSET buffer info
renderer use that info to use appropriate buffer section 

buffer_pool should have similar interface to buffer

renderer : draw single object
renderer : draw batch of objects (should be on same buffer)

object should be reloaded on buffer if vertexattributes changed

smart buffer

Object -> primitive 
Object -> INdexedPrimitive
Object -> Batch

Storage
{
    span []
    
}

// Could be VBO or EBO
template <Key, Value = byte>
Buffer : public ContiguousMappedStorage
{
    Data = <Value>

    void uploadAll()
    bool upload(Key key)


}

Vertex Buffer can be the same for different objects
Vertex Array too, until number or size of Attributes change

Vertex Array should know Object's Vertex Buffer position

On renderer draw, check if Object's Vertex Attributes changed size: in that 
case, update Enable... and upload on buffer, upload buffer
If it changed only Data, upload on buffer, upload buffer

Store latest vertex attributes infos into buffer state
in render loop, if attributes change load on buffer,
if attributes pointer changed reupload buffer on ai 