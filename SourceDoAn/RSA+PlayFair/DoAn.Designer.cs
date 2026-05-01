namespace RSA_PlayFair
{
    partial class DoAn
    {
        private System.ComponentModel.IContainer components = null;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null)) components.Dispose();
            base.Dispose(disposing);
        }

        private void InitializeComponent()
        {
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.txtPlayfairKey = new System.Windows.Forms.TextBox();
            this.txtPlayfairInput = new System.Windows.Forms.TextBox();
            this.txtPlayfairResult = new System.Windows.Forms.TextBox();
            this.btnPlayfairEncrypt = new System.Windows.Forms.Button();
            this.txtRSAP = new System.Windows.Forms.TextBox();
            this.txtRSAQ = new System.Windows.Forms.TextBox();
            this.txtRSAInput = new System.Windows.Forms.TextBox();
            this.txtRSAResult = new System.Windows.Forms.TextBox();
            this.btnRSAEncrypt = new System.Windows.Forms.Button();
            this.lblRSAKeys = new System.Windows.Forms.Label();

         
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Size = new System.Drawing.Size(434, 461);

            
            this.tabPage1.Text = "Giải thuật Playfair";
            this.txtPlayfairKey.PlaceholderText = "Nhập từ khóa (Key)...";
            this.txtPlayfairKey.Location = new System.Drawing.Point(30, 30);
            this.txtPlayfairKey.Size = new System.Drawing.Size(350, 27);

            this.btnPlayfairEncrypt.Text = "Mã hóa văn bản";
            this.btnPlayfairEncrypt.Location = new System.Drawing.Point(30, 70);
            this.btnPlayfairEncrypt.Size = new System.Drawing.Size(150, 35);
            this.btnPlayfairEncrypt.BackColor = System.Drawing.Color.LightBlue;
            this.btnPlayfairEncrypt.Click += new System.EventHandler(this.btnPlayfairEncrypt_Click);

            this.txtPlayfairInput.PlaceholderText = "Nhập văn bản cần mã hóa...";
            this.txtPlayfairInput.Location = new System.Drawing.Point(30, 120);
            this.txtPlayfairInput.Multiline = true;
            this.txtPlayfairInput.Size = new System.Drawing.Size(350, 80);

            this.txtPlayfairResult.PlaceholderText = "Kết quả Playfair sẽ hiện ở đây...";
            this.txtPlayfairResult.Location = new System.Drawing.Point(30, 220);
            this.txtPlayfairResult.Multiline = true;
            this.txtPlayfairResult.Size = new System.Drawing.Size(350, 80);
            this.txtPlayfairResult.ReadOnly = true;

           
            this.tabPage2.Text = "Giải thuật RSA";
            this.txtRSAP.PlaceholderText = "Số p";
            this.txtRSAP.Location = new System.Drawing.Point(30, 30);
            this.txtRSAP.Size = new System.Drawing.Size(160, 27);

            this.txtRSAQ.PlaceholderText = "Số q";
            this.txtRSAQ.Location = new System.Drawing.Point(220, 30);
            this.txtRSAQ.Size = new System.Drawing.Size(160, 27);

            this.btnRSAEncrypt.Text = "Thực hiện RSA";
            this.btnRSAEncrypt.Location = new System.Drawing.Point(30, 70);
            this.btnRSAEncrypt.Size = new System.Drawing.Size(150, 35);
            this.btnRSAEncrypt.BackColor = System.Drawing.Color.LightGreen;
            this.btnRSAEncrypt.Click += new System.EventHandler(this.btnRSAEncrypt_Click);

            this.txtRSAInput.PlaceholderText = "Nhập thông điệp (dạng số)...";
            this.txtRSAInput.Location = new System.Drawing.Point(30, 120);
            this.txtRSAInput.Size = new System.Drawing.Size(350, 27);

            this.txtRSAResult.PlaceholderText = "Kết quả mã hóa RSA...";
            this.txtRSAResult.Location = new System.Drawing.Point(30, 160);
            this.txtRSAResult.Size = new System.Drawing.Size(350, 27);
            this.txtRSAResult.ReadOnly = true;

            this.lblRSAKeys.Location = new System.Drawing.Point(30, 200);
            this.lblRSAKeys.Size = new System.Drawing.Size(350, 100);
            this.lblRSAKeys.Text = "Thông tin Key: Đợi tính toán...";

           
            this.tabPage1.Controls.AddRange(new System.Windows.Forms.Control[] { txtPlayfairKey, btnPlayfairEncrypt, txtPlayfairInput, txtPlayfairResult });
            this.tabPage2.Controls.AddRange(new System.Windows.Forms.Control[] { txtRSAP, txtRSAQ, btnRSAEncrypt, txtRSAInput, txtRSAResult, lblRSAKeys });
            this.tabControl1.TabPages.AddRange(new System.Windows.Forms.TabPage[] { tabPage1, tabPage2 });

            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(434, 461);
            this.Controls.Add(this.tabControl1);
            this.Text = "Đồ án UIT - An toàn mạng";
        }

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TextBox txtPlayfairKey;
        private System.Windows.Forms.TextBox txtPlayfairInput;
        private System.Windows.Forms.TextBox txtPlayfairResult;
        private System.Windows.Forms.Button btnPlayfairEncrypt;
        private System.Windows.Forms.TextBox txtRSAP;
        private System.Windows.Forms.TextBox txtRSAQ;
        private System.Windows.Forms.TextBox txtRSAInput;
        private System.Windows.Forms.TextBox txtRSAResult;
        private System.Windows.Forms.Button btnRSAEncrypt;
        private System.Windows.Forms.Label lblRSAKeys;
    }
}
