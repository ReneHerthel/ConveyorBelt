//
// Created by Silt on 14.05.2017.
//

#ifndef CONVEYORBELT_ISERIALIZEABLE_H
#define CONVEYORBELT_ISERIALIZEABLE_H


#include <cstdint>

typedef struct serialized{
    uint32_t size; /*!< Size of the object in bytes*/
    void* obj; /*!<The serialized object */
};

class ISerializable {
public:
    /**
     * This function serializes the Object to an array of bytes.
     * @return The array with the serialized object and its size in bytes.
     */
    virtual serialized serialize() = 0;

    /**
     * Deserialize an Object so it can be used again
     * @tparam T The type of object that should be made by calling this function,
     *          shall be equal to the class calling
     * @return The object created
     */
    template<class T> virtual T deserialize(serialized ser) = 0;
};


#endif //CONVEYORBELT_ISERIALIZEABLE_H
