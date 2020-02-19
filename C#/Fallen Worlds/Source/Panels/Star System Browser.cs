using System;
using System.Collections.Generic;
using System.Text;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace App
{
    class Star_System_Browser
    {
        // Constants
        private const int Spacing = 192;
        private const int StartX = 100;
        private Sprite m_sprite = null;
        private int m_starsystem;
        private float[] m_rotationvalue;

        public Star_System_Browser()
        {
            m_starsystem = -1;
            m_rotationvalue = new float[Universe.MaxPlanetsPerSystem];

            // Setup rendering
            m_sprite = new Sprite(Game.m_engine.m_device);
        }

        ~Star_System_Browser()
        {
            m_sprite.Dispose();
        }

        private static float a = 0.0f;
        public void Render(int starsystem, int highlightedplanet, float relativeupdate)
        {
            // Different system|
            if (starsystem != m_starsystem)
            {
                m_starsystem = starsystem;
                for (int i = 0; i < Game.m_universe.m_starsystems[m_starsystem].Count; i++)
                {
                    m_rotationvalue[i] = 0.0f;
                }
            }

            // Render each planet it turn
            int pos = 0;
            foreach (int planet in Game.m_universe.m_starsystems[m_starsystem])
            {
                m_sprite.Begin(SpriteFlags.SortTexture);
                Game.m_universe.m_planets[planet].Draw2D(m_sprite, StartX + (pos * Spacing), 500, m_rotationvalue[pos]);
                pos++;
                m_sprite.End();
            }

            // Rotate selected planet
            m_rotationvalue[highlightedplanet] += 3.0f * relativeupdate;
        }
    }
}
