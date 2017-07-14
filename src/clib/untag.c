/*-
 * Copyright (c) 2014-2017 Carsten Sonne Larsen <cs@innolan.net>
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
 * Project homepage:
 * https://amath.innolan.net
 * 
 */

#include "amathc.h"

void Untag(char* destination, const char* source, texttag tags[], unsigned int tagcount)
{
    const char *pos, *tmp, *tag;
    char* dest;
    int unsigned i, j, found;

    pos = source;
    dest = destination;

    while (*pos != '\0')
    {
        if (*pos != '#')
        {
            (*dest++ = *pos++);
        }
        else
        {
            // Try to replace tag
            found = 0;
            for (i = 0; i < tagcount; i++)
            {
                tag = tags[i].tag;
                tmp = pos;
                j = 0;
                while (*tmp != '\0' && *tag != '\0' && *tmp == *tag)
                {
                    tmp++;
                    tag++;
                    j++;
                }

                if (j > 1 && *(--tag) == '#')
                {
                    // Tag found. Now replace.
                    tag = tags[i].text;
                    while ((*dest++ = *tag++));
                    dest--;
                    pos = tmp;
                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                (*dest++ = *pos++);
            }
        }
    }
    *dest = '\0';
}
