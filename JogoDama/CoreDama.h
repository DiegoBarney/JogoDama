#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define LINHAS 8
#define COLUNAS 8

#define TAM_LINHAS_INTERFACE 15
#define TAM_COLUNAS_INTERFACE 8

#define TECLA_MENU_OPCAO_JOGAR 1
#define TECLA_MENU_OPCAO_TUTORIAL 2
#define TECLA_MENU_OPCAO_SAIR 3

#define TECLA_GAMEPLAY_DIRECIONAL_UP 88
#define TECLA_GAMEPLAY_DIRECIONAL_DOWN 22
#define TECLA_GAMEPLAY_DIRECIONAL_RIGHT 66
#define TECLA_GAMEPLAY_DIRECIONAL_LEFT 44
#define TECLA_GAMEPLAY_ACAO_CAPTURAR 55
#define TECLA_GAMEPLAY_ACAO_SOLTAR 33
#define TECLA_GAMEPLAY_ACAO_CANCELAR_JOGADA 11
#define TECLA_GAMEPLAY_ACAO_SAIR_DO_JOGO 118

#define TECLA_INVALIDA 999

#define TABULEIRO_PONTEIRO_INICIAL 0

#define AVISOS_MOVIMENTO_INVALIDO_POSICAO_OCUPADA " MOVIMENTO DE PECA INVALIDO, ESTA POSICAO JA ESTA OCUPADA."
#define AVISOS_MOVIMENTO_INVALIDO_POSICAO_ERRADA  " MOVIMENTO DE PECA INVALIDO, ESTA PECA NAO PODE FAZER ESTE MOVIMENTO."
#define AVISOS_MOVIMENTAR_PECA_BRANCA " MOVIMENTO DE PECA INVALIDO, VOCE DEVE MOVIMENTAR AS PECAS BRANCAS."
#define AVISOS_MOVIMENTAR_PECA_PRETA " MOVIMENTO DE PECA INVALIDO, VOCE DEVE MOVIMENTAR AS PECAS PRETAS."
#define AVISOS_MOVIMENTAR_SEM_PECA " MOVIMENTO DE PECA INVALIDO, VOCE ESTA TENTANDO CAPTURAR UMA CASA SEM PECA."
#define AVISOS_MOVIMENTAR_CAPTURA_INCORRETA1 " MOVIMENTO DE PECA INVALIDO, VOCE ESTA TENTANDO CAPTURAR MAIS DE UMA PECA POR VEZ."
#define AVISOS_SEM_AVISOS " "


#define PECA_BRANCA 'B'
#define PECA_PRETA 'P'
#define PECA_BRANCA_DAMA 'Q'
#define PECA_PRETA_DAMA 'K'
#define PECA_SELECIONADA 'S'
#define VAZIO ' '
#define PONTEIRO_DIRECIONAL '*'

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
