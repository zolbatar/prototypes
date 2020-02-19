using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace App
{
    static class Program
    {
        [STAThread]
        static void Main()
        {
            Game game = new Game();
            game.Run();
        }
    }
}