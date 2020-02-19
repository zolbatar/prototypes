using System;
using System.Drawing;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace App
{
    class Engine : Form
    {
        // Device
        public Device m_device = null;
        private Engine_Text m_enginetext = null;
        private Engine_Sprite m_enginesprite = null;
        private PresentParameters m_presentParameters = null;
        private Timer tmrMain;
        private System.ComponentModel.IContainer components;
        public bool m_CloseRequested = false;
        private int m_ticks = 0;

        // Constructor
        public Engine()
        {
            // Setup window
            this.ClientSize = new Size(1024, 768);
            this.Text = Game.ProjectName;
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Engine_FormClosing);

            // Create parameters and device
            try
            {
                m_presentParameters = new PresentParameters();
                m_presentParameters.Windowed = true;
                m_presentParameters.SwapEffect = SwapEffect.Flip ;
                m_presentParameters.AutoDepthStencilFormat = DepthFormat.D16;
                m_presentParameters.BackBufferCount = 1;
                m_presentParameters.PresentationInterval = PresentInterval.Immediate;
                m_device = new Device(
                        0,
                        DeviceType.Hardware,
                        this,
                        CreateFlags.SoftwareVertexProcessing,
                        m_presentParameters);
            }
            catch (DirectXException)
            {
                throw new Exception("Engine initialisation failed.");
            }

            // Device settings
            m_device.RenderState.ZBufferEnable = false;

            // Dependent engines and objects
            m_enginetext = new Engine_Text();
            m_enginesprite = new Engine_Sprite();
        }

        ~Engine()
        {
            if (m_device != null)
            {
                m_device.Dispose();
            }
        }

        public void Render_Begin(float relativeupdate)
        {
            // Clear backbuffer
            m_device.Clear(ClearFlags.Target, Color.Black, 1.0f, 0);

            // Begin scene
            m_device.BeginScene();

            m_enginesprite.Render();
            m_enginetext.Render();
        }

        public void Render_End()
        {
            // End scene
            m_device.EndScene();
            m_device.Present();
        }

        private void Engine_FormClosing(object sender, FormClosingEventArgs e)
        {
            m_CloseRequested = true;
        }

        public void Add(Engine_Text_Item item)
        {
            m_enginetext.m_list.Add(item);
        }

        public void Remove(Engine_Text_Item item)
        {
            if (!m_enginetext.m_list.Remove(item))
                throw new Exception("Unable to remove item from Text list.");
        }

        public void Add(Engine_Sprite_Item item)
        {
            m_enginesprite.m_list.Add(item);
        }

        public void Remove(Engine_Sprite_Item item)
        {
            if (!m_enginesprite.m_list.Remove(item))
                throw new Exception("Unable to remove item from Sprite list.");
        }

        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.tmrMain = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // Engine
            // 
            this.ClientSize = new System.Drawing.Size(292, 266);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Engine";
            this.ShowIcon = false;
            this.ResumeLayout(false);

        }

    }
}
