/*
 * Copyright (c) 2015-2017 Carsten Sonne Larsen  <cs@innolan.dk>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef AMATH_SYSTEM_IO_H
#define AMATH_SYSTEM_IO_H
/******************************************************************************/
/**
 * @file  io.h
 * @brief System dependent I/O
 *
 */
/******************************************************************************/
#include "clib.h"
#include "platform.h"
#include "system/program.h"

#define CPROCNAME      "amath_console"
/******************************************************************************/
#ifdef  AOS3
#define AMIGADOS_NAME  "dos.library"
#define AMIGADOS_REV   33L
#define INTUITION_REV  37L
#define INTUITION_NAME "intuition.library"
#define GRAPHICS_REV   37L
#define GRAPHICS_NAME  "graphics.library"
#define LOCALE_REV     38L
#define LOCALE_NAME    "locale.library"
#define DEVCONSOLE     "console.device"
#define PORTCR         "RKM.console.read"
#define PORTCW         "RKM.console.write"
#define CATALOG_HELP   "amath-help.catalog"
#define CATALOG_IDEN   "amath-ident.catalog"
#define CATALOG_TEXT   "amath-text.catalog"
#define CATALOG_KEYW   "amath-keyword.catalog"
#define CATALOG_DEF    OC_BuiltInLanguage, "english"
#endif
/******************************************************************************/
#if defined(AROS) || defined(MORPHOS) || defined(AOS4)
#define AMIGADOS_NAME  "dos.library"
#define AMIGADOS_REV   33L
#define INTUITION_REV  37L
#define INTUITION_NAME "intuition.library"
#define GRAPHICS_REV   37L
#define GRAPHICS_NAME  "graphics.library"
#define LOCALE_REV     38L
#define LOCALE_NAME    "locale.library"
#define DEVCONSOLE     "console.device"
#define PORTCR         "RKM.console.read"
#define PORTCW         "RKM.console.write"
#define CATALOG_HELP   "amath-help.catalog"
#define CATALOG_IDEN   "amath-ident.catalog"
#define CATALOG_TEXT   "amath-text.catalog"
#define CATALOG_KEYW   "amath-keyword.catalog"
#define CATALOG_DEF    OC_BuiltInLanguage, "english"
#endif
/******************************************************************************/
extern const char *vers;
extern class Program *Program;
class Program* CreateProgram(int,char **);
class Language* CreateLanguage();
class PreferencesBase* CreatePreferences();
class FilesystemBase* CreateFilesystem();
class GraphWindow* CreateGraphWindow();
void WriteToShell(const char*);
void Cleanup();
/******************************************************************************/
#endif
