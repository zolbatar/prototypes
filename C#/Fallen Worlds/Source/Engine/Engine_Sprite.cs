using System;
using System.Collections.Generic;
using System.Text;

namespace App
{
    class Engine_Sprite
    {
        public List<Engine_Sprite_Item> m_list = null;

        public Engine_Sprite()
        {
            m_list = new List<Engine_Sprite_Item>();
        }

        public void Render()
        {
            foreach (Engine_Sprite_Item item in m_list)
            {
                item.Render();
            }
        }
    }
}
