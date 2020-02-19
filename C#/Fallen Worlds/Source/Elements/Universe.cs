using System;
using System.IO;
using System.Collections.Generic;
using System.Text;

namespace App
{
    class Universe
    {
        // Planet constants
        public const int MaxPlanetsPerSystem = 5;
        private const int NumPlanetsPerClass = 8;
        private const int NumClasses = 4;
        private const int PlanetWidth = 128;
        private const int PlanetHeight = 128;
        private const string PlanetFileExtension = "*.png";
        private const string PlanetPath = @"..\..\Media\Planets\Class ";
        public Engine_Texture[] m_planets;
        public List<int>[] m_starsystems = null;
        private int m_nostarsystems;

        public Universe()
        {
            // Load planets
            m_planets = new Engine_Texture[NumPlanetsPerClass * NumClasses];
            int i = 0;

            // Class 1
            for (int planet = 1; planet <= NumClasses; planet++)
            {
                foreach (string file in Directory.GetFiles(PlanetPath + planet.ToString() + @"\", PlanetFileExtension))
                {
                    m_planets[i++] = new Engine_Texture(file, PlanetWidth, PlanetHeight);
                }
            }
        }

        public void Build(int nostarsystems, int maxplanetsperstarsystem)
        {
            m_nostarsystems = nostarsystems;
            m_starsystems = new List<int>[m_nostarsystems];
            
            // An array of used planets, don't use twice
            bool[] Used = new bool[NumPlanetsPerClass * NumClasses];
            for (int i = 0; i < NumPlanetsPerClass * NumClasses; i++)
                Used[i] = false;

            // Create a universe!
            for (int i = 0; i < nostarsystems; i++)
            {
                m_starsystems[i] = new List<int>();
                int numplanets = Game.m_random.Next(maxplanetsperstarsystem - 2) + 2;
                for (int j = 0; j < numplanets; j++)
                {
                    int planet = Game.m_random.Next(NumPlanetsPerClass * NumClasses);
                    while (Used[planet])
                    {
                        planet = Game.m_random.Next(NumPlanetsPerClass * NumClasses);
                    }
                    m_starsystems[i].Add(planet);
                }
            }
        }
    }
}