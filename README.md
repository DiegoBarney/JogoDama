# Jogo Dama
/*using System;
using log4net;
using System.Diagnostics;
using System.Reflection;
using System.IO;

namespace PB.Utils
{
    public class Log
    {
        private static readonly ILog log4;

        public enum Nivel
        {
            DEBUG, INFO, WARN, ERROR, FATAL
        }

        /// <summary>
        /// Bloco de Código Estático para carregar o arquivo de configuração 
        /// </summary>
        static Log()
        {
            log4 = LogManager.GetLogger(typeof(Log));
            string pathFileConfig = new Uri(System.Reflection.Assembly.GetExecutingAssembly().CodeBase).LocalPath + ".config";
            FileInfo fileConfigLog = new FileInfo(pathFileConfig);

            log4net.Config.XmlConfigurator.ConfigureAndWatch(fileConfigLog);
        }

        #region METODOS PRIVADOS
        /// <summary>
        /// Metodo para Retornar o namespace + o nome do Metodo
        /// </summary>
        /// <returns></returns>
        private static string getNomeCompletoMetodo()
        {
            int contadorStack = 1;
            StackFrame stackFrame = new StackFrame(contadorStack);
            MethodBase TempMethod = stackFrame.GetMethod();

            while (TempMethod.Name.Equals("write"))
            {
                stackFrame = new StackFrame(++contadorStack);
                TempMethod = stackFrame.GetMethod();
            }
            string nomeMetodo = TempMethod.Name.Equals(".ctor") ? "CONSTRUCTOR" : TempMethod.Name;
            string nomeClasse = (((System.Reflection.MemberInfo)(TempMethod)).ReflectedType).FullName;
            //return nomeMetodo;
            return nomeClasse + "." + nomeMetodo;
        }

        /// <summary>
        /// Metodo que loga uma Exception com uma mensagem
        /// </summary>
        /// <param name="nivelLog">DEBUG, WARNING...</param>
        /// <param name="exception">Exception que ocorreu na aplicação</param>
        /// <param name="mensagem">mensagem para Logar</param>
        private static void logar(Nivel nivelLog, Exception exception, string mensagem = "")
        {
            switch (nivelLog)
            {
                case Nivel.DEBUG:
                    log4.Debug(mensagem, exception);
                    break;
                case Nivel.INFO:
                    log4.Info(mensagem, exception);
                    break;
                case Nivel.WARN:
                    log4.Warn(mensagem, exception);
                    break;
                case Nivel.ERROR:
                    log4.Error(mensagem, exception);
                    break;
                case Nivel.FATAL:
                    log4.Fatal(mensagem, exception);
                    break;
            }
        }

        private static void logar(Nivel nivelLog, string mensagem = "")
        {
            switch (nivelLog)
            {
                case Nivel.DEBUG:
                    log4.Debug(mensagem);
                    break;
                case Nivel.INFO:
                    log4.Info(mensagem);
                    break;
                case Nivel.WARN:
                    log4.Warn(mensagem);
                    break;
                case Nivel.ERROR:
                    log4.Error(mensagem);
                    break;
                case Nivel.FATAL:
                    log4.Fatal(mensagem);
                    break;
            }
        }
        #endregion

        #region METODOS PUBLICOS
        public static void write(Nivel nivelLog, Exception exception, params string[] mensagem)
        {
            string msg = getNomeCompletoMetodo() + " ";

            for (int i = 0; i < mensagem.Length; i++)
            {
                msg += mensagem[i] + " ";
            }

            logar(nivelLog, exception, msg);
        }

        public static void write(Nivel nivelLog, params string[] mensagem)
        {
            string msg = getNomeCompletoMetodo() + " ";

            for (int i = 0; i < mensagem.Length; i++)
            {
                msg += mensagem[i] + " ";
            }

            logar(nivelLog, msg);
        }
        #endregion
    }
}*/
Este é o melhor jogo de Dama criado na linguagem C/C++ com interface DOS, tem uma excelente jogabilidade e um belo UI\UX com o velho e bom DOS, durante sua jogada você pode mover-se e realizar ações no tabuleiro de 64 casas:
![alt text](https://github.com/DiegoBarney/JogoDama/blob/main/Jogo_Dama.PNG?raw=true)
