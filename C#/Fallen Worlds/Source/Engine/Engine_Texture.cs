using System;
using System.Drawing;
using System.Collections.Generic;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace App
{
    class Engine_Texture
    {
        public Texture m_texture = null;
        private int m_width = 0, m_height = 0;
        private Point m_center;

        public Engine_Texture(String filename, int width, int height)
        {
            m_width = width;
            m_height = height;
            m_center = new Point(m_width / 2, m_height / 2);

            // Load texture
            m_texture = TextureLoader.FromFile(
                Game.m_engine.m_device,
                filename,
                width, height, 1,
                Usage.None,
                Format.A8R8G8B8,
                Pool.Managed,
                Filter.None,
                Filter.None ,
                unchecked((int)(0xFF000000)));
        }

        public void Draw2D(Sprite sprite, int x, int y)
        {
            sprite.Draw2D(m_texture,
                m_center,
                0.0f,
                new Point(x, y), Color.White);
        }

        public void Draw2D(Sprite sprite, int x, int y, float angle)
        {
            sprite.Draw2D(m_texture,
                m_center,
                (float)((double)angle * Math.PI / 180),
                new Point(x, y), Color.White);
        }
    }
}
