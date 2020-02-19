using System;
using System.Drawing;
using System.Collections.Generic;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace App
{
    class Engine_Sprite_Item
    {
        private Engine_Texture m_texture = null;
        private int m_x, m_y;
        private float m_angle;
        private Sprite m_sprite = null;

        public Engine_Sprite_Item(Engine_Texture texture, int x, int y, float angle)
        {
            m_texture = texture;
            m_x = x;
            m_y = y;
            m_angle = angle;
            m_sprite = new Sprite(Game.m_engine.m_device);
        }

        public void Render()
        {
            m_sprite.Begin(SpriteFlags.AlphaBlend);
            if (m_angle != 0.0f)
                m_texture.Draw2D(m_sprite, m_x, m_y, m_angle);
            else
                m_texture.Draw2D(m_sprite, m_x, m_y);
            m_sprite.End();
        }

        public void Rotate(float angle)
        {
            m_angle += angle;
            m_angle %= 360;
        }

    }
}
