using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Numerics;
using System.Windows.Forms;

namespace RSA_PlayFair
{
    public partial class DoAn : Form
    {
        public DoAn()
        {
            InitializeComponent();
        }

        private void btnPlayfairEncrypt_Click(object sender, EventArgs e)
        {
            try
            {
                string key = txtPlayfairKey.Text.ToUpper().Replace("J", "I");
                string input = txtPlayfairInput.Text.ToUpper().Replace("J", "I").Replace(" ", "");
                if (string.IsNullOrEmpty(key) || string.IsNullOrEmpty(input)) return;

                char[,] matrix = GenerateMatrix(key);
                txtPlayfairResult.Text = ProcessPlayfair(matrix, input);
            }
            catch (Exception ex) { MessageBox.Show("Lỗi: " + ex.Message); }
        }

        private char[,] GenerateMatrix(string key)
        {
            string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
            string combined = new string((key + alphabet).Distinct().ToArray());
            char[,] m = new char[5, 5];
            for (int i = 0; i < 25; i++) m[i / 5, i % 5] = combined[i];
            return m;
        }

        private string ProcessPlayfair(char[,] m, string input)
        {
           
            string result = "";
            for (int i = 0; i < input.Length; i += 2)
            {
                char a = input[i];
                char b = (i + 1 < input.Length) ? input[i + 1] : 'X';
                if (a == b) { b = 'X'; i--; }

                Point p1 = GetPos(m, a);
                Point p2 = GetPos(m, b);
                if (p1.X == p2.X) result += m[p1.X, (p1.Y + 1) % 5].ToString() + m[p2.X, (p2.Y + 1) % 5].ToString();
                else if (p1.Y == p2.Y) result += m[(p1.X + 1) % 5, p1.Y].ToString() + m[(p2.X + 1) % 5, p2.Y].ToString();
                else result += m[p1.X, p2.Y].ToString() + m[p2.X, p1.Y].ToString();
            }
            return result;
        }

        private Point GetPos(char[,] m, char c)
        {
            for (int r = 0; r < 5; r++)
                for (int col = 0; col < 5; col++)
                    if (m[r, col] == c) return new Point(r, col);
            return new Point(-1, -1);
        }

        private void btnRSAEncrypt_Click(object sender, EventArgs e)
        {
            try
            {
                BigInteger p = BigInteger.Parse(txtRSAP.Text);
                BigInteger q = BigInteger.Parse(txtRSAQ.Text);
                BigInteger n = p * q;
                BigInteger phi = (p - 1) * (q - 1);
                BigInteger ev = 65537;
                BigInteger d = ModInverse(ev, phi);
                BigInteger m = BigInteger.Parse(txtRSAInput.Text);

                txtRSAResult.Text = BigInteger.ModPow(m, ev, n).ToString();
                lblRSAKeys.Text = $"N: {n}\nE (Công khai): {ev}\nD (Bí mật): {d}";
            }
            catch { MessageBox.Show("Vui lòng nhập các số nguyên hợp lệ!"); }
        }

        public static BigInteger ModInverse(BigInteger a, BigInteger n)
        {
            BigInteger t = 0, nt = 1, r = n, nr = a;
            while (nr != 0)
            {
                BigInteger q = r / nr;
                (t, nt) = (nt, t - q * nt);
                (r, nr) = (nr, r - q * nr);
            }
            return t < 0 ? t + n : t;
        }
    }
}