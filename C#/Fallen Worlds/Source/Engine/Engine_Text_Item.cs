using System;
using System.Drawing;
using System.Drawing.Text;
using System.Collections.Generic;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;


namespace App
{
    class Engine_Text_Item
    {
        private string m_text;
        private Color m_colour;
        private Microsoft.DirectX.Direct3D.Font m_font;
        private System.Drawing.Font m_windowsfont;
        private Rectangle m_size;
        private DrawTextFormat m_format;
        private Sprite m_sprite = null;

        public Engine_Text_Item(string text, Color colour, int x, int y, int width, int height, System.Drawing.Font font)
        {
            m_sprite = new Sprite(Game.m_engine.m_device);
            m_windowsfont = font;
            m_font = new Microsoft.DirectX.Direct3D.Font(Game.m_engine.m_device, font);
            m_size = new Rectangle(x, y, x + width, y + height);
            m_format = 0;
            m_text = text;
            m_colour = colour;
        }

        ~Engine_Text_Item()
        {
            m_sprite.Dispose();
            m_font.Dispose();
        }

        public void Render()
        {
            m_sprite.Begin(SpriteFlags.AlphaBlend);
            if (m_font.DrawText(m_sprite, m_text, m_size, m_format, m_colour) == 0)
                throw new Exception("You cannot draw text.  Error drawing text.");
            m_sprite.End();
        }

    }
}
