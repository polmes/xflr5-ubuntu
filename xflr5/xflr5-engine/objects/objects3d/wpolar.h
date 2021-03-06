/****************************************************************************

    WPolar Class
    Copyright (C) 2005-2016 Andre Deperrois

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


/** @file
 *
 * This class defines the polar object for the 3D analysis of wings and planes
 *
 */


#ifndef WPOLAR_H
#define WPOLAR_H


#include <objects/objects3d/plane.h>

/**
*@brief
*    This class defines the polar object used in 2D and 3D calculations
*
    The class stores both the analysis parameters and the analysis results.

    Each instance of this class is uniquely associated to an instance of a Wing or a Plane object.
    The data is stored in International Standard Units, i.e. meters, seconds, kg, and Newtons.
    Angular data is stored in degrees
*/
#include <QVarLengthArray>


#include <analysis3d/analysis3d_enums.h>
#include "wingopp.h"
#include "planeopp.h"

#define MAXPOLARPOINTS   5000     /**< The max number of points on a polar. */
#define MAXEXTRADRAG 4
#define MAXCONTROLS 100


class XFLR5ENGINELIBSHARED_EXPORT WPolar
{
    //    friend class LLTAnalysis;


public:
    WPolar();

    void addPlaneOpPoint(PlaneOpp* pPOpp);
    void replacePOppDataAt(int pos, PlaneOpp *pPOpp);
    void insertPOppDataAt(int pos, PlaneOpp *pPOpp);
    void insertDataAt(int pos, double Alpha, double Beta, double QInf, double Ctrl, double Cl, double CY, double ICd, double PCd, double GCm,
                      double ICm, double VCm, double GRm, double GYm, double IYm, double VYm, double XCP, double YCP,
                      double ZCP, double Cb, double XNP);
    void calculatePoint(int iPt);
    void copy(WPolar *pWPolar);
    void duplicateSpec(WPolar *pWPolar);
    QVector<double> *getWPlrVariable(int iVar);
    void remove(int i);
    void remove(double alpha);
    void clearData();
    void retrieveInertia(Plane *pPlane);

    bool serializeWPlrWPA(QDataStream &ar, bool bIsStoring);
    bool serializeWPlrXFL(QDataStream &ar, bool bIsStoring);

    XFLR5::enumPolarType polarType()           const {return m_WPolarType;}       /**< returns the type of the polar as an index in the enumeration. */
    XFLR5::enumAnalysisMethod analysisMethod() const {return m_AnalysisMethod;}   /**< returns the analysis method of the polar as an index in the enumeration. */
    void setPolarType(XFLR5::enumPolarType type) {m_WPolarType=type;}
    void setAnalysisMethod(XFLR5::enumAnalysisMethod method) {m_AnalysisMethod=method;}

    bool isLLTMethod()         {return m_AnalysisMethod==XFLR5::LLTMETHOD;}
    bool isVLMMethod()         {return m_AnalysisMethod==XFLR5::VLMMETHOD;}
    bool isPanel4Method()      {return m_AnalysisMethod==XFLR5::PANEL4METHOD;}
    bool isQuadMethod()        {return isPanel4Method() || isVLMMethod();}
    bool isTriCstMethod()      {return m_AnalysisMethod==XFLR5::TRICSTMETHOD;}
    bool isTriLinearMethod()   {return m_AnalysisMethod==XFLR5::TRILINMETHOD;}
    bool isTriangleMethod()    {return isTriCstMethod() || isTriLinearMethod();}

    QString const &polarName() const {return m_WPlrName;}       /**< returns the polar's name as a QString object. */
    QString const &planeName() const {return m_PlaneName;}      /**< returns the name of the polar's parent object as a QString object. */
    void setPolarName(QString const &name) {m_WPlrName=name;}
    void setPlaneName(QString const &name) {m_PlaneName=name;}

    double density()    const {return m_Density;}        /**< returns the fluid's density, in IS units. */
    double viscosity()  const {return m_Viscosity;}      /**< returns the fluid's kinematic viscosity, in IS units. */
    void setDensity(double f) {m_Density=f;}
    void setViscosity(double f) {m_Viscosity=f;}

    bool isFixedSpeedPolar() const    {return m_WPolarType==XFLR5::FIXEDSPEEDPOLAR;}      /**< returns true if the polar is of the FIXEDSPEEDPOLAR type, false otherwise >*/
    bool isFixedLiftPolar()  const    {return m_WPolarType==XFLR5::FIXEDLIFTPOLAR;}       /**< returns true if the polar is of the FIXEDLIFTPOLAR type, false otherwise >*/
    bool isFixedaoaPolar()   const    {return m_WPolarType==XFLR5::FIXEDAOAPOLAR;}        /**< returns true if the polar is of the FIXEDAOAPOLAR type, false otherwise >*/
    bool isStabilityPolar()  const    {return m_WPolarType==XFLR5::STABILITYPOLAR;}       /**< returns true if the polar is of the STABILITYPOLAR type, false otherwise >*/
    bool isBetaPolar()       const    {return m_WPolarType==XFLR5::BETAPOLAR;}            /**< returns true if the polar is of the BETAPOLAR type, false otherwise >*/

    /** @todo remove remaining non-const reference access functions */
    bool &bThinSurfaces() {return m_bThinSurfaces;}  /**< returns true if the analysis if using thin surfaces, i.e. VLM, false if 3D Panels for the Wing objects. */
    bool &bWakeRollUp()  {return m_bWakeRollUp;}
    bool &bTilted() {return m_bTiltedGeom; }
    bool &bGround() {return m_bGround;}
    bool &bIgnoreBodyPanels() {return m_bIgnoreBodyPanels;}
    bool &bViscous() {return m_bViscous;}
    bool &bVLM1() {return m_bVLM1;}
    bool &bAutoInertia() {return m_bAutoInertia;}
    bool bDirichlet() {return m_BoundaryCondition==XFLR5::DIRICHLET;}

    int polarFormat() {return m_PolarFormat;}
    void setPolarFormat(int fmt) {m_PolarFormat=fmt;}

    XFLR5::enumBC &boundaryCondition() {return m_BoundaryCondition;}

    XFLR5::enumRefDimension  const &referenceDim() const {return m_ReferenceDim;}
    double referenceArea()  const{return m_referenceArea;}
    double referenceSpanLength()  const {return m_referenceSpanLength;}
    double referenceChordLength() const {return m_referenceChordLength;}
    void setReferenceDim(XFLR5::enumRefDimension dim) {m_ReferenceDim=dim;}
    void setReferenceArea(double a) {m_referenceArea=a;}
    void setReferenceSpanLength(double l) {m_referenceSpanLength=l;}
    void setReferenceChordLength(double c) {m_referenceChordLength=c;}


    double velocity()     const {return m_QInfSpec;}
    double Alpha()        const {return m_AlphaSpec;}
    double Beta()         const {return m_BetaSpec;}
    double Phi()          const {return m_BankAngle;}
    double mass()         const {return m_Mass;}
    double groundHeight() const {return m_Height;}

    void setVelocity(double Q)     {m_QInfSpec=Q;}
    void setAlpha(double aoa)      {m_AlphaSpec=aoa;}
    void setBeta(double b)         {m_BetaSpec=b;}
    void setPhi(double phi)        {m_BankAngle=phi;}
    void setMass(double m)         {m_Mass=m;}
    void setGroundHeight(double h) {m_Height=h;}

    Vector3d CoG() const {return m_CoG;}
    double CoGIxx() const {return m_CoGIxx;}
    double CoGIyy() const {return m_CoGIyy;}
    double CoGIzz() const {return m_CoGIzz;}
    double CoGIxz() const {return m_CoGIxz;}

    void setCoG(Vector3d cg) {m_CoG=cg;}
    void setCoGx(double x) {m_CoG.x=x;}
    void setCoGy(double y) {m_CoG.y=y;}
    void setCoGz(double z) {m_CoG.z=z;}
    void setCoGIxx(double ixx) {m_CoGIxx=ixx;}
    void setCoGIyy(double iyy) {m_CoGIyy=iyy;}
    void setCoGIzz(double izz) {m_CoGIzz=izz;}
    void setCoGIxz(double ixz) {m_CoGIxz=ixz;}

    bool isVisible() const {return m_bIsVisible;}
    int points()     const {return m_PointStyle;}
    int curveStyle() const {return m_Style;}
    int curveWidth() const {return m_Width;}
    ObjectColor curveColor()  const {return m_Color;}

    void setVisible(bool bvis) {m_bIsVisible=bvis;}
    void setPoints(int pts) {m_PointStyle=pts;}
    void setCurveStyle(int s) {m_Style=s;}
    void setCurveWidth(int w) {m_Width=w;}
    void setCurveColor(ObjectColor colour) {m_Color=colour;}

    int dataSize() const {return m_Alpha.size();}

private:

    int m_Style, m_Width, m_PointStyle;
    bool m_bIsVisible;
    ObjectColor m_Color;

    bool     m_bVLM1;              /**< true if the analysis is performed with horseshoe vortices, flase if quad rings */
    //    bool     m_bDirichlet;         /**< true if Dirichlet boundary conditions should be applied, false if Neumann */
    bool     m_bGround;            /**< true if ground effect should be taken into account in the analysis */
    bool     m_bIgnoreBodyPanels;  /**< true if the body panels should be ignored in the analysis */
    bool     m_bThinSurfaces;      /**< true if VLM, false if 3D-panels */
    bool     m_bTiltedGeom;        /**< true if the analysis should be performed on the tilted geometry */
    bool     m_bViscous;           /**< true if the analysis is viscous */
    bool     m_bWakeRollUp;        /**< true if wake roll-up  should be taken into account in the analysis */
    int      m_PolarFormat;        /**< the identification number which references the format used to serialize the data */

    XFLR5::enumBC m_BoundaryCondition;
    XFLR5::enumRefDimension  m_ReferenceDim;        /**< Describes the origin of the refernce area : 1 if planform area, else projected area */

    QString  m_WPlrName;            /**< the polar's name */
    QString  m_PlaneName;          /**< the name of the parent wing or plane */


    double m_referenceArea;          /**< The reference area for the calculation of aero coefficients */
    double m_referenceChordLength;   /**< The reference length = the mean aero chord, for the calculation of aero coefficients */
    double m_referenceSpanLength;    /**< The reference span for the calculation of aero coefficients */

    Vector3d       m_CoG;                  /**< the position of the CoG */
    double        m_Density;              /**< The fluid's density */
    double        m_Mass;                 /**< The mass for type 2 and type 7 polars */

    XFLR5::enumAnalysisMethod m_AnalysisMethod;  /**< The method used for the analysis. May be one of the following types : LLTMETHOD, VLMMETHOD, PANELMETHOD */
    XFLR5::enumPolarType      m_WPolarType;      /**< The type of analysis. May be one of the following types :FIXEDSPEEDPOLAR, FIXEDLIFTPOLAR, FIXEDAOAPOLAR, STABILITYPOLAR */

public:
    bool     m_bRelaxWake;         /**< true if wake relaxation is implemented */
    bool     m_bAutoInertia;       /**< true if the inertia to be taken into account is the one of the parent plane */
    double   m_CoGIxx;             /**< The Ixx component of the inertia tensor, w.r.t. the CoG origin */
    double   m_CoGIxz;             /**< The Ixz component of the inertia tensor, w.r.t. the CoG origin */
    double   m_CoGIyy;             /**< The Iyy component of the inertia tensor, w.r.t. the CoG origin */
    double   m_CoGIzz;             /**< The Izz component of the inertia tensor, w.r.t. the CoG origin */

    double   m_inertiaGain[7];

    int      m_nControls;          /**< the number of control surfaces for this wing or plane */
    int      m_NXWakePanels;       /**< the number of wake panels in each streamwise column */
    double   m_AlphaSpec;          /**< the angle of attack for type 4 & 5 polars */
    double   m_BetaSpec;           /**< The sideslip angle for type 1,2, 4 polars */
    double   m_BankAngle;          /**< The bank angle */
    double   m_QInfSpec;           /**< the freestream velocity for type 1 & 5 polars */
    double   m_Height;             /**< The plane flight altitude, used if ground effect is to be taken into account*/
    double   m_Viscosity;          /**< The fluid's kinematic viscosity */

    double   m_WakePanelFactor;    /**< the ratio between the length of two wake panels in the x direction */
    double   m_TotalWakeLength;    /**< the wake's length x MAC; defines the position of the Trefftz plane */

    QVarLengthArray<double> m_ControlGain;      /**< the scaling factor for each of the control surfaces */

    QVector <double>  m_1Cl;        /**< 1/Cl, special for Matthieu */
    QVector <double>  m_Alpha;      /**< the angle of attack */
    QVector <double>  m_Beta;       /**< the sideslip angle */
    QVector <double>  m_QInfinite;  /**< the free stream speed - type 2 WPolars */
    QVector <double>  m_Cl32Cd;     /**< the power factor */
    QVector <double>  m_ClCd;       /**< the glide ratio */
    QVector <double>  m_CL;         /**< lift coef. */

    QVector <double>  m_Ctrl;       /**< Ctrl variable */
    QVector <double>  m_CY;         /**< Side Force */
    QVector <double>  m_FX;         /**< the total drag */


    QVector <double>  m_FY;         /**< the total side force */
    QVector <double>  m_FZ;         /**< the total wing lift */
    QVector <double>  m_Gamma;      /**< glide angle = Atan(Cx/Cz), in degrees */
    QVector <double>  m_GCm;        /**< Total Pitching Moment coefficient */
    QVector <double>  m_GRm;        /**< Total rolling moment */

    QVector <double>  m_GYm;        /**< Total yawing moment coefficient */
    QVector <double>  m_ICd;        /**< induced drag coef. */
    QVector <double>  m_ICm;        /**< Induced Pitching Moment coefficient */
    QVector <double>  m_IYm;        /**< induced yawing moment coefficient */
    QVector <double>  m_Rm;         /**< the total rolling moment */
    QVector <double>  m_Pm;         /**< the total pitching moment */
    QVector <double>  m_MaxBending; /**< the max bending moment at the root chord */

    QVector <double>  m_Oswald;     /**< Oswald's efficiency factor */
    QVector <double>  m_PCd;        /**< profile drag coef. */

    complex<double> m_EigenValue[8][MAXPOLARPOINTS]; /**< until we have a QVector<complex<double>> ? */
    QVector <double>  m_PhugoidFrequency;        /**< the phugoid's frequency, as a result of stability analysis only */
    QVector <double>  m_PhugoidDamping;          /**< the phugoid's damping factor, as a result of stability analysis only */
    QVector <double>  m_RollDampingT2;           /**< the time to double or half for the damping of the roll-damping mode, as a result of stability analysis only */
    QVector <double>  m_ShortPeriodDamping;      /**< the damping of the short period mode, as a result of stability analysis only */
    QVector <double>  m_ShortPeriodFrequency;    /**< the frequency of the short period mode, as a result of stability analysis only */
    QVector <double>  m_DutchRollDamping;        /**< the damping of the Dutch roll mode, as a result of stability analysis only */
    QVector <double>  m_DutchRollFrequency;      /**< the frequency of the Dutch roll mode, as a result of stability analysis only */
    QVector <double>  m_SpiralDampingT2;         /**< the time to double or half for the damping of the spiral mode, as a result of stability analysis only >*/

    QVector <double>  m_XCpCl;                   /**< XCp.Cl, used in calculation of neutral point position >*/
    QVector <double>  m_SM;                      /**< (XCP-XCmRef)/m.a.c; >*/
    QVector <double>  m_TCd;                     /**< the total drag coeficient >*/
    QVector <double>  m_VCm;                     /**< the viscous Pitching Moment coefficient >*/
    QVector <double>  m_VertPower;               /**< the power for steady horizontal flight = m.g.Vz >*/
    QVector <double>  m_HorizontalPower;         /**< the power for steady horizontal flight = Fx.Vx >*/

    QVector <double>  m_Vx;         /**< the horizontal component of the velocity */
    QVector <double>  m_VYm;        /**< Profile yawing Moment coefficient */
    QVector <double>  m_Vz;         /**< the sink speed = sqrt(2mg/rho/S)/powerfactor */
    QVector <double>  m_XCP;        /**< the centre of pressure X-position relative to the wing's root LE */
    QVector <double>  m_XNP;        /**< the position of the neutral point, as a result of stability analysis only */

    QVector <double>  m_YCP;        /**< the centre of pressure Y-position relative to the wing's root LE */
    QVector <double>  m_Ym;         /**< the total yawing moment */
    QVector <double>  m_ZCP;        /**< the centre of pressure Z-position relative to the wing's root LE */

    QVector <double>  m_ExtraDrag;  /**< the custom extra drag in addition to the induced and viscous drag parts */

    QVector <double>  m_Mass_var;   /**< the mass calculated as ref_mass + gain*control */
    QVector <double>  m_CoG_x;      /**< the CoG position calculated as ref_CoG_x + gain*control */
    QVector <double>  m_CoG_z;      /**< the CoG position calculated as ref_CoG_z + gain*control */

    double m_ExtraDragArea[MAXEXTRADRAG], m_ExtraDragCoef[MAXEXTRADRAG];

    double m_XNeutralPoint;       /**< Neutral point position, calculated from d(XCp.Cl)/dCl >*/
};

#endif
