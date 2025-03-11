namespace WindowsFormsApplication1
{
    partial class Form1
    {
        /// <summary>
        /// Variable del diseñador requerida.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén utilizando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben eliminar; false en caso contrario, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido del método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            this.label1 = new System.Windows.Forms.Label();
            this.IP = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.consultaPokedex = new System.Windows.Forms.RadioButton();
            this.Longitud = new System.Windows.Forms.RadioButton();
            this.Bonito = new System.Windows.Forms.RadioButton();
            this.Usuario = new System.Windows.Forms.Label();
            this.Contraseña = new System.Windows.Forms.Label();
            this.textUsu = new System.Windows.Forms.TextBox();
            this.textContra = new System.Windows.Forms.TextBox();
            this.SignIn = new System.Windows.Forms.Button();
            this.SignUp = new System.Windows.Forms.Button();
            this.textContraR = new System.Windows.Forms.TextBox();
            this.textUsuR = new System.Windows.Forms.TextBox();
            this.ContraseñaRegistrarse = new System.Windows.Forms.Label();
            this.UsuarioRegistrarse = new System.Windows.Forms.Label();
            this.textConRR = new System.Windows.Forms.TextBox();
            this.RepetirContraseña = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(41, 58);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(40, 31);
            this.label1.TabIndex = 0;
            this.label1.Text = "IP";
            // 
            // IP
            // 
            this.IP.Location = new System.Drawing.Point(112, 64);
            this.IP.Margin = new System.Windows.Forms.Padding(4);
            this.IP.Name = "IP";
            this.IP.Size = new System.Drawing.Size(172, 22);
            this.IP.TabIndex = 2;
            this.IP.Text = "192.168.56.102";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(383, 57);
            this.button1.Margin = new System.Windows.Forms.Padding(4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(112, 38);
            this.button1.TabIndex = 4;
            this.button1.Text = "conectar";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(61, 140);
            this.button2.Margin = new System.Windows.Forms.Padding(4);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(100, 28);
            this.button2.TabIndex = 5;
            this.button2.Text = "Enviar";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.groupBox1.Controls.Add(this.consultaPokedex);
            this.groupBox1.Controls.Add(this.Longitud);
            this.groupBox1.Controls.Add(this.Bonito);
            this.groupBox1.Controls.Add(this.button2);
            this.groupBox1.Location = new System.Drawing.Point(32, 430);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox1.Size = new System.Drawing.Size(484, 249);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Peticion";
            this.groupBox1.Enter += new System.EventHandler(this.groupBox1_Enter);
            // 
            // consultaPokedex
            // 
            this.consultaPokedex.AutoSize = true;
            this.consultaPokedex.Location = new System.Drawing.Point(41, 105);
            this.consultaPokedex.Margin = new System.Windows.Forms.Padding(4);
            this.consultaPokedex.Name = "consultaPokedex";
            this.consultaPokedex.Size = new System.Drawing.Size(233, 20);
            this.consultaPokedex.TabIndex = 9;
            this.consultaPokedex.TabStop = true;
            this.consultaPokedex.Text = "Dame informacion de Charmander";
            this.consultaPokedex.UseVisualStyleBackColor = true;
            // 
            // Longitud
            // 
            this.Longitud.AutoSize = true;
            this.Longitud.Location = new System.Drawing.Point(41, 77);
            this.Longitud.Margin = new System.Windows.Forms.Padding(4);
            this.Longitud.Name = "Longitud";
            this.Longitud.Size = new System.Drawing.Size(245, 20);
            this.Longitud.TabIndex = 7;
            this.Longitud.TabStop = true;
            this.Longitud.Text = "Dime la primera pratida que he echo";
            this.Longitud.UseVisualStyleBackColor = true;
            // 
            // Bonito
            // 
            this.Bonito.AutoSize = true;
            this.Bonito.Location = new System.Drawing.Point(41, 49);
            this.Bonito.Margin = new System.Windows.Forms.Padding(4);
            this.Bonito.Name = "Bonito";
            this.Bonito.Size = new System.Drawing.Size(214, 20);
            this.Bonito.TabIndex = 8;
            this.Bonito.TabStop = true;
            this.Bonito.Text = "Dime cuantos pokemons tengo";
            this.Bonito.UseVisualStyleBackColor = true;
            // 
            // Usuario
            // 
            this.Usuario.AutoSize = true;
            this.Usuario.Location = new System.Drawing.Point(73, 140);
            this.Usuario.Name = "Usuario";
            this.Usuario.Size = new System.Drawing.Size(54, 16);
            this.Usuario.TabIndex = 7;
            this.Usuario.Text = "Usuario";
            // 
            // Contraseña
            // 
            this.Contraseña.AutoSize = true;
            this.Contraseña.Location = new System.Drawing.Point(73, 181);
            this.Contraseña.Name = "Contraseña";
            this.Contraseña.Size = new System.Drawing.Size(76, 16);
            this.Contraseña.TabIndex = 8;
            this.Contraseña.Text = "Contraseña";
            // 
            // textUsu
            // 
            this.textUsu.Location = new System.Drawing.Point(166, 140);
            this.textUsu.Margin = new System.Windows.Forms.Padding(4);
            this.textUsu.Name = "textUsu";
            this.textUsu.Size = new System.Drawing.Size(172, 22);
            this.textUsu.TabIndex = 9;
            // 
            // textContra
            // 
            this.textContra.Location = new System.Drawing.Point(166, 181);
            this.textContra.Margin = new System.Windows.Forms.Padding(4);
            this.textContra.Name = "textContra";
            this.textContra.Size = new System.Drawing.Size(172, 22);
            this.textContra.TabIndex = 10;
            // 
            // SignIn
            // 
            this.SignIn.Location = new System.Drawing.Point(76, 223);
            this.SignIn.Margin = new System.Windows.Forms.Padding(4);
            this.SignIn.Name = "SignIn";
            this.SignIn.Size = new System.Drawing.Size(112, 38);
            this.SignIn.TabIndex = 11;
            this.SignIn.Text = "Inicia Sesion";
            this.SignIn.UseVisualStyleBackColor = true;
            this.SignIn.Click += new System.EventHandler(this.SignIn_Click);
            // 
            // SignUp
            // 
            this.SignUp.Location = new System.Drawing.Point(475, 263);
            this.SignUp.Margin = new System.Windows.Forms.Padding(4);
            this.SignUp.Name = "SignUp";
            this.SignUp.Size = new System.Drawing.Size(112, 38);
            this.SignUp.TabIndex = 16;
            this.SignUp.Text = "Registrarse";
            this.SignUp.UseVisualStyleBackColor = true;
            this.SignUp.Click += new System.EventHandler(this.SignUp_Click);
            // 
            // textContraR
            // 
            this.textContraR.Location = new System.Drawing.Point(565, 187);
            this.textContraR.Margin = new System.Windows.Forms.Padding(4);
            this.textContraR.Name = "textContraR";
            this.textContraR.Size = new System.Drawing.Size(172, 22);
            this.textContraR.TabIndex = 15;
            // 
            // textUsuR
            // 
            this.textUsuR.Location = new System.Drawing.Point(565, 146);
            this.textUsuR.Margin = new System.Windows.Forms.Padding(4);
            this.textUsuR.Name = "textUsuR";
            this.textUsuR.Size = new System.Drawing.Size(172, 22);
            this.textUsuR.TabIndex = 14;
            // 
            // ContraseñaRegistrarse
            // 
            this.ContraseñaRegistrarse.AutoSize = true;
            this.ContraseñaRegistrarse.Location = new System.Drawing.Point(472, 187);
            this.ContraseñaRegistrarse.Name = "ContraseñaRegistrarse";
            this.ContraseñaRegistrarse.Size = new System.Drawing.Size(76, 16);
            this.ContraseñaRegistrarse.TabIndex = 13;
            this.ContraseñaRegistrarse.Text = "Contraseña";
            // 
            // UsuarioRegistrarse
            // 
            this.UsuarioRegistrarse.AutoSize = true;
            this.UsuarioRegistrarse.Location = new System.Drawing.Point(472, 146);
            this.UsuarioRegistrarse.Name = "UsuarioRegistrarse";
            this.UsuarioRegistrarse.Size = new System.Drawing.Size(54, 16);
            this.UsuarioRegistrarse.TabIndex = 12;
            this.UsuarioRegistrarse.Text = "Usuario";
            // 
            // textConRR
            // 
            this.textConRR.Location = new System.Drawing.Point(565, 223);
            this.textConRR.Margin = new System.Windows.Forms.Padding(4);
            this.textConRR.Name = "textConRR";
            this.textConRR.Size = new System.Drawing.Size(172, 22);
            this.textConRR.TabIndex = 18;
            // 
            // RepetirContraseña
            // 
            this.RepetirContraseña.AutoSize = true;
            this.RepetirContraseña.Location = new System.Drawing.Point(472, 223);
            this.RepetirContraseña.Name = "RepetirContraseña";
            this.RepetirContraseña.Size = new System.Drawing.Size(76, 32);
            this.RepetirContraseña.TabIndex = 17;
            this.RepetirContraseña.Text = "Repite la \r\nContraseña";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(988, 692);
            this.Controls.Add(this.textConRR);
            this.Controls.Add(this.RepetirContraseña);
            this.Controls.Add(this.SignUp);
            this.Controls.Add(this.textContraR);
            this.Controls.Add(this.textUsuR);
            this.Controls.Add(this.ContraseñaRegistrarse);
            this.Controls.Add(this.UsuarioRegistrarse);
            this.Controls.Add(this.SignIn);
            this.Controls.Add(this.textContra);
            this.Controls.Add(this.textUsu);
            this.Controls.Add(this.Contraseña);
            this.Controls.Add(this.Usuario);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.IP);
            this.Controls.Add(this.label1);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox IP;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton Longitud;
        private System.Windows.Forms.RadioButton Bonito;
        private System.Windows.Forms.Label Usuario;
        private System.Windows.Forms.Label Contraseña;
        private System.Windows.Forms.TextBox textUsu;
        private System.Windows.Forms.TextBox textContra;
        private System.Windows.Forms.Button SignIn;
        private System.Windows.Forms.Button SignUp;
        private System.Windows.Forms.TextBox textContraR;
        private System.Windows.Forms.TextBox textUsuR;
        private System.Windows.Forms.Label ContraseñaRegistrarse;
        private System.Windows.Forms.Label UsuarioRegistrarse;
        private System.Windows.Forms.TextBox textConRR;
        private System.Windows.Forms.Label RepetirContraseña;
        private System.Windows.Forms.RadioButton consultaPokedex;
    }
}

