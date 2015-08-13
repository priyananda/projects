// __________________________________________________________________________________________________
//    GLGooey Graphical User Interface for OpenGL
//    Copyright (c) 2004 Niel Waldren
//
// This software is provided 'as-is', without any express or implied warranty. In no event will
// the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose, including commercial
// applications, and to alter it and redistribute it freely, subject to the following restrictions:
//
//     1. The origin of this software must not be misrepresented; you must not claim that you
//        wrote the original software. If you use this software in a product, an acknowledgment
//        in the product documentation would be appreciated but is not required.
//
//     2. Altered source versions must be plainly marked as such, and must not be misrepresented
//        as being the original software.
//
//     3. This notice may not be removed or altered from any source distribution.
//
// __________________________________________________________________________________________________
#ifndef __GOOEY_NIL_IMAGE_H__
#define __GOOEY_NIL_IMAGE_H__



#include "glgooey/services/interfaces/Image.h"

#include "glgooey/core/Position.h"

// *************************************************************************************************
//  Forward declarations
namespace Gooey
{
    namespace Core
    {
        class Size;
    }
}
// *************************************************************************************************




// *************************************************************************************************
namespace Gooey
{




// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//! \brief Nil image which just returns an empty black image
class NilImage : public Image
{
    // ----------------------------------------------------------------------------------------------
    //  Xstruction
    // ----------------------------------------------------------------------------------------------
protected:
    //! Default Constructor
    NilImage() : Image("") {}

    //! Destructor
    virtual ~NilImage() {}



    // ---------------------------------------------------------------------------------------------
    //  Public Interface
    // ---------------------------------------------------------------------------------------------
public:
    // Commented in the base class
    virtual Core::Size size() const { return Core::Size(4, 4); }
    virtual size_t numberOfBitsPerPixel() const { return 24; }
    virtual const unsigned char* data() const { return data_; }
    virtual unsigned char* data() { return data_; }
    virtual void release() {}


    // ---------------------------------------------------------------------------------------------
    //  Implementation
    // ----------------------------------------------------------------------------------------------
private:
    static unsigned char data_[];  //!< Pointer to the raw data that represents the image

    friend class Image;
};
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<






// *************************************************************************************************
} // namespace Gooey




#endif
