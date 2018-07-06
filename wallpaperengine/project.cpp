#include <irrlicht/irrlicht.h>
#include <iostream>
#include <fstream>

#include "fs/fileResolver.h"

#include "project.h"
#include "irrlicht.h"

namespace wp
{
    project::project (irr::io::path baseDirectory)
    {
        irr::io::path projectFile = wp::fs::resolver.resolveOnWorkingDirectory ("project.json");

        std::ifstream _in (projectFile.c_str ());
        this->m_content = "";
        this->m_content.append (std::istreambuf_iterator<char> (_in), std::istreambuf_iterator<char> ());
        this->m_projectFile = json::parse (this->m_content);

        json::const_iterator file_it = this->m_projectFile.find ("file");
        json::const_iterator name_it = this->m_projectFile.find ("title");
        json::const_iterator type_it = this->m_projectFile.find ("type");

        if (file_it != this->m_projectFile.end ())
        {
            // load scene file
            this->m_file = wp::fs::resolver.resolveOnWorkingDirectory (*file_it);
            this->m_scene = new scene (this->m_file.c_str ());
        }

        if (type_it != this->m_projectFile.end ())
        {
            this->m_type = type_it.value ();
        }

        if (name_it != this->m_projectFile.end ())
        {
            this->m_title = name_it.value ();
        }
    }
}