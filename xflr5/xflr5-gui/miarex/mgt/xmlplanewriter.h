/****************************************************************************

    XmlPlaneWriter Class
    Copyright (C) 2015 Andre Deperrois

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*****************************************************************************/

#ifndef XMLPLANEWRITER_H
#define XMLPLANEWRITER_H

#include <QXmlStreamWriter>
#include <QFile>

#include <objects/objects3d/vector3d.h>

class Plane;
class Wing;
class Body;
class PointMass;
class XMLPlaneWriter : public QXmlStreamWriter
{
public:
    XMLPlaneWriter(QFile &XFile);
    void writeXMLPlane(Plane *m_pPlane);
    void writeXMLBody(Body *pBody);
    void writeXMLWing(Wing &wing);
    void writeBody(Body *pBody, Vector3d position, double lengthUnit, double massUnit);
    void writeWing(Wing &wing, Vector3d position, double Ry);


private:
    void writeHeader();
    void writePointMass(PointMass *ppm, double massUnit, double lengthUnit);
    void writeColor(QColor color);

};

#endif // XMLPLANEWRITER_H
