using System;
using System.IO;
using System.Drawing;
using System.Drawing.Text;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using System.Windows.Forms;

namespace App
{
    class Game
    {
        // Constants
        public const string ProjectName = "Fallen Worlds";
        public const string MediaPath = @"..\..\Media\";
        public const string MediaFontsPath = @"..\..\Media\Fonts\";

        // Engines
        public static Engine m_engine = null;
        public static Universe m_universe = null;
        public static Star_System_Browser m_starsystembrowser = null;

        // Camera
        private float camera_pos_x = 0.0f, camera_pos_y = 0.0f, camera_pos_z = -5.0f;
        private float camera_tgt_x = 0.0f, camera_tgt_y = 0.0f, camera_tgt_z = 0.0f;

        // Fonts
        static public PrivateFontCollection m_fonts = new PrivateFontCollection();
        private uint PrivateFontCounter = 0;
        private Font m_font_standard_00_r;
        private Font m_font_continuummedium_16_r;
        private Font m_font_federation;

        // Globals
        public static Random m_random = null;

        // Sprites
        Engine_Texture m_testtex = null;

        public Game()
        {
            // Random number generator
            m_random = new Random((int)DateTime.Now.Ticks);

            // Initialise the engine
            m_engine = new Engine();

            // Game specific engines
            m_universe = new Universe();
            m_starsystembrowser = new Star_System_Browser();

            // Setup embedded fonts
            m_fonts.AddFontFile(MediaFontsPath + "Continuum Medium.ttf");
            m_font_continuummedium_16_r = new Font(m_fonts.Families[PrivateFontCounter++], 14.0f, FontStyle.Regular);
            m_fonts.AddFontFile(MediaFontsPath + "Federation_Starfleet_Hull_23rd.ttf");
            m_font_federation = new Font(m_fonts.Families[PrivateFontCounter++], 14.0f, FontStyle.Regular);

            // Setup system fonts
            m_font_standard_00_r = new Font("Tahoma", 8.0f, FontStyle.Regular);

            // Load sprite0
            m_testtex = new Engine_Texture(MediaPath + @"mosquito.bmp", 160, 100);
        }

        public void Run()
        {
            // Build the universe
            m_universe.Build(5, 5);

            // Show the form
            m_engine.Show();

            Engine_Text_Item a = new Engine_Text_Item(
                "Sample Text!", Color.White,
                40, 50, 50, 50,
                m_font_standard_00_r);
            Engine_Text_Item b = new Engine_Text_Item(
                "Sample Text!", Color.White,
                40, 100, 50, 50,
                m_font_continuummedium_16_r);
            Engine_Text_Item c = new Engine_Text_Item(
                "Lots of Sample Text!", Color.White,
                40, 150, 50, 50,
                m_font_federation);
            Engine_Sprite_Item sa = new Engine_Sprite_Item(m_testtex, 200, 100, 0.0f);
            Engine_Sprite_Item sb = new Engine_Sprite_Item(m_testtex, 200, 100, 0.0f);

            m_engine.Add(a);
            m_engine.Add(b);
            m_engine.Add(c);
            m_engine.Add(sa);
            m_engine.Add(sb);

            // While form is valid, run the game loop
            long lastticks = DateTime.Now.Ticks;
            while (m_engine.Created)
            {
                long ticks = (DateTime.Now.Ticks - lastticks) / 10000L;
                lastticks = DateTime.Now.Ticks;
                float engineticks = (float)ticks / 100.0f;

                // Render cycle
                m_engine.Render_Begin(engineticks);
                m_starsystembrowser.Render(0, 0, engineticks);
                m_engine.Render_End();
                sa.Rotate(1.0f);

                // Handle any events, for example closing window
                Application.DoEvents();
                if (m_engine.m_CloseRequested)
                    break;

                // Sleep, allow other threads some CPU
                Thread.Sleep(10);
            }

            // Cleanup
            m_engine.Dispose();
        }
    }        
}
