using System;
using System.Collections.Generic;

namespace App
{
    class Engine_Text
    {
        private Engine m_engine = null;
        public List<Engine_Text_Item> m_list = null;

        public Engine_Text()
        {
            m_list = new List<Engine_Text_Item>();
        }

        public void Remove(Engine_Text_Item item)
        {
            m_list.Remove(item);
        }

        public void Render()
        {
            foreach (Engine_Text_Item item in m_list)
            {
                item.Render();
            }
        }
    }
}
