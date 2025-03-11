using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        Socket server;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //Inicio Sesion
            Usuario.Visible = false;
            textUsu.Visible = false;
            Contraseña.Visible = false;
            textContra.Visible = false;
            SignIn.Visible = false;

            //Resitrarse
            UsuarioRegistrarse.Visible = false;
            textUsuR.Visible = false;
            ContraseñaRegistrarse.Visible = false;
            textContraR.Visible = false;
            RepetirContraseña.Visible = false;
            textConRR.Visible = false;
            SignUp.Visible = false;

            //Consultas 
            groupBox1.Visible = false;
           
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //Creamos un IPEndPoint con el ip del servidor y puerto del servidor 
            //al que deseamos conectarnos
            IPAddress direc = IPAddress.Parse(IP.Text);
            IPEndPoint ipep = new IPEndPoint(direc, 9050);
            

            //Creamos el socket 
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                server.Connect(ipep);//Intentamos conectar el socket
                this.BackColor = Color.Green;
                MessageBox.Show("Conectado");

                //Inicio Sesion
                Usuario.Visible = true;
                textUsu.Visible = true;
                Contraseña.Visible = true;
                textContra.Visible = true;
                SignIn.Visible = true;

                //Resitrarse
                UsuarioRegistrarse.Visible = true;
                textUsuR.Visible = true;
                ContraseñaRegistrarse.Visible = true;
                textContraR.Visible = true;
                RepetirContraseña.Visible = true;
                textConRR.Visible = true;
                SignUp.Visible = true;

                //Consultas 
                groupBox1.Visible = true;

            }
            catch (SocketException ex)
            {
                //Si hay excepcion imprimimos error y salimos del programa con return 
                MessageBox.Show("No he podido conectar con el servidor");
                return;
            }

        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (Longitud.Checked) //Consulta Primera partida que he echo
            {
                string mensaje = "3/" + textUsu.Text;
                // Enviamos al servidor el nombre tecleado
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);
                mensaje = Encoding.ASCII.GetString(msg2).Split(',')[0];
                MessageBox.Show("La Primera partida que hize fue" + mensaje);
            }
            else if (consultaPokedex.Checked) //Consulta que pokemon tiene mayo vida.
            {
                string mensaje = "4/" + textUsu.Text;
                // Enviamos al servidor el nombre tecleado
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);
                mensaje = Encoding.ASCII.GetString(msg2).Split(',')[0];

                MessageBox.Show("El pokemon con mas vida es el " + mensaje);

            }
            else if (Bonito.Checked) //Consulta Cuantos pokemos tengo.
            {
                string mensaje = "5/" + textUsu.Text;
                // Enviamos al servidor el nombre tecleado
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);
                mensaje = Encoding.ASCII.GetString(msg2).Split(',')[0];
                MessageBox.Show("Tengo " + mensaje + " pokemons");
            }
            else
                MessageBox.Show("Seleciona la estadistica que quieras consultar");

            // Se terminó el servicio. 
            // Nos desconectamos
            this.BackColor = Color.Gray;
            server.Shutdown(SocketShutdown.Both);
            server.Close();

        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void SignUp_Click(object sender, EventArgs e)
        {
            if (textContraR == textConRR && textConRR.Text.Length != 0 && textContraR.Text.Length != 0 && textUsuR.Text.Length != 0)
            {
                string mensaje = "1/" + textUsuR.Text + textContra.Text;
                // Enviamos al servidor el nombre tecleado
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);
                mensaje = Encoding.ASCII.GetString(msg2).Split(',')[0];

                if (mensaje == "Ok")
                    MessageBox.Show("Te has registrado correctamente");
                else
                    MessageBox.Show("Este Usuario ya esta en uso Prueba con otra");
            }
            else
            {
                MessageBox.Show("Las contraseñas son diferentes, mira si hay un error Ortografico. O rellena los campos vacios");
            }
        }

        private void SignIn_Click(object sender, EventArgs e)
        {
            if (textUsu.Text.Length != 0 && textContra.Text.Length != 0)
            {
                string mensaje = "2/" + textUsu.Text + textContra.Text;
                // Enviamos al servidor el nombre tecleado
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                //Recibimos la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);
                mensaje = Encoding.ASCII.GetString(msg2).Split(',')[0];

                if (mensaje == "Ok")
                    MessageBox.Show("Bienvenido");
                else
                    MessageBox.Show("Contraseña y/o Usuario son incorrectos");
            }
            else
                MessageBox.Show("Rellena los campos que estan vacios");
            
        }
    }
}
