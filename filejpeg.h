/*
License: GPL-2
  An electronic filing cabinet: scan, print, stack, arrange
 Copyright (C) 2009 Simon Glass, chch-kiwi@users.sourceforge.net
 .
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 .
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 .
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

X-Comment: On Debian GNU/Linux systems, the complete text of the GNU General
 Public License can be found in the /usr/share/common-licenses/GPL file.
*/
/*
   Project:    Maxview
   Author:     Simon Glass
   Copyright:  2001-2009 Bluewater Systems Ltd, www.bluewatersys.com
   File:       filepdfx.h
   Started:    26/6/09

   This file implmenents a JPEG file, which is just a single one page image.

   This is implemented using QT's built-in JPEG features (QImage).
*/

#include "file.h"


class Filejpeg : public File
   {
   Q_OBJECT
public:
   Filejpeg (const QString &dir, const QString &filename, Desk *desk);
   ~Filejpeg ();

   /*********** functions which the base class should implement **********/

   // load / save / create

   virtual err_info *load (void);  // was desk->ensureMax

   virtual err_info *create (void);

   virtual err_info *flush (void);

   virtual err_info *remove (void);


   // accessing and changing metadata

   virtual int pagecount (void);

   virtual err_info *getPageTitle (int pagenum, QString &title);

   virtual err_info *getAnnot (e_annot type, QString &text);

   virtual err_info *putAnnot (QHash<int, QString> &updates);

   virtual err_info *putEnvelope (QStringList &env);

   virtual err_info *getPageText (int pagenum, QString &str);

   virtual int getSize (void);

   virtual err_info *renamePage (int pagenum, QString &name);

   err_info *getImageInfo (int pagenum, QSize &size,
         QSize &true_size, int &bpp, int &image_size, int &compressed_size,
         QDateTime &timestamp);

   virtual err_info *getPreviewInfo (int pagenum, QSize &Size, int &bpp);



   // image related
   virtual QPixmap pixmap (bool recalc = false);

   virtual err_info *getPreviewPixmap (int pagenum, QPixmap &pixmap, bool blank);

   virtual err_info *getImage (int pagenum, bool do_scale,
               QImage &image, QSize &Size, QSize &trueSize, int &bpp, bool blank);


   // operations on files

   virtual err_info *addPage (const Filepage *mp, bool flush);

   virtual err_info *removePages (QBitArray &pages,
         QByteArray &del_info, int &count);

   virtual err_info *restorePages (QBitArray &pages,
      QByteArray &del_info, int count);

   virtual err_info *unstackPages (int pagenum, int pagecount, bool remove,
               File *dest);

   virtual err_info *stackStack (File *src);

   virtual err_info *duplicate (File *&fnew, File::e_type type, const QString &uniq,
      int odd_even, Operation &op, bool &supported);


   /*********** end of functions which the base class should implement ******/

private:
   err_info *load_annot (void);

   err_info *create_annot (void);

   e_annot fromTag (QString tag);

   QString toTag (e_annot annot);

   /** Check if a page number is valid. This returns an error unless the
     page is 0.

     \param pagenum  page number to check
     \return NULL if ok, else an error */
   err_info *checkPage (int pagenum);


private:
   QImage _image;
   QPixmap _pixmap;
   QString _page_title; /* Title of first (only) page */
   bool _changed;       /* true if the image has been changed */
   };

class Filejpegpage : public Filepage
{
public:
   Filejpegpage (void);
   ~Filejpegpage (void);

   /** compress the page */
   err_info *compress (void);
   };
