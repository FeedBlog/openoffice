/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_drawinglayer.hxx"

#include <drawinglayer/primitive2d/polypolygonprimitive2d.hxx>
#include <basegfx/polygon/b2dpolypolygontools.hxx>
#include <basegfx/tools/canvastools.hxx>
#include <drawinglayer/primitive2d/fillgradientprimitive2d.hxx>
#include <drawinglayer/primitive2d/maskprimitive2d.hxx>
#include <drawinglayer/primitive2d/fillhatchprimitive2d.hxx>
#include <basegfx/matrix/b2dhommatrix.hxx>
#include <drawinglayer/primitive2d/fillgraphicprimitive2d.hxx>
#include <drawinglayer/primitive2d/polygonprimitive2d.hxx>
#include <drawinglayer/primitive2d/drawinglayer_primitivetypes2d.hxx>
#include <basegfx/matrix/b2dhommatrixtools.hxx>
#include <vcl/graph.hxx>

//////////////////////////////////////////////////////////////////////////////

using namespace com::sun::star;

//////////////////////////////////////////////////////////////////////////////

namespace drawinglayer
{
	namespace primitive2d
	{
		Primitive2DSequence PolyPolygonHairlinePrimitive2D::create2DDecomposition(const geometry::ViewInformation2D& /*rViewInformation*/) const
		{
			const basegfx::B2DPolyPolygon aPolyPolygon(getB2DPolyPolygon());
			const sal_uInt32 nCount(aPolyPolygon.count());

			if(nCount)
			{
				Primitive2DSequence aRetval(nCount);

				for(sal_uInt32 a(0L); a < nCount; a++)
				{
					aRetval[a] = Primitive2DReference(new PolygonHairlinePrimitive2D(aPolyPolygon.getB2DPolygon(a), getBColor()));
				}

				return aRetval;
			}
			else
			{
				return Primitive2DSequence();
			}
		}

		PolyPolygonHairlinePrimitive2D::PolyPolygonHairlinePrimitive2D(const basegfx::B2DPolyPolygon& rPolyPolygon, const basegfx::BColor& rBColor)
		:	BufferedDecompositionPrimitive2D(),
			maPolyPolygon(rPolyPolygon),
			maBColor(rBColor)
		{
		}

		bool PolyPolygonHairlinePrimitive2D::operator==(const BasePrimitive2D& rPrimitive) const
		{
			if(BufferedDecompositionPrimitive2D::operator==(rPrimitive))
			{
				const PolyPolygonHairlinePrimitive2D& rCompare = (PolyPolygonHairlinePrimitive2D&)rPrimitive;

				return (getB2DPolyPolygon() == rCompare.getB2DPolyPolygon() 
					&& getBColor() == rCompare.getBColor());
			}

			return false;
		}

		basegfx::B2DRange PolyPolygonHairlinePrimitive2D::getB2DRange(const geometry::ViewInformation2D& /*rViewInformation*/) const
		{
			// return range
			return basegfx::tools::getRange(getB2DPolyPolygon());
		}

		// provide unique ID
		ImplPrimitrive2DIDBlock(PolyPolygonHairlinePrimitive2D, PRIMITIVE2D_ID_POLYPOLYGONHAIRLINEPRIMITIVE2D)

	} // end of namespace primitive2d
} // end of namespace drawinglayer

//////////////////////////////////////////////////////////////////////////////

namespace drawinglayer
{
	namespace primitive2d
	{
		Primitive2DSequence PolyPolygonMarkerPrimitive2D::create2DDecomposition(const geometry::ViewInformation2D& /*rViewInformation*/) const
		{
			const basegfx::B2DPolyPolygon aPolyPolygon(getB2DPolyPolygon());
			const sal_uInt32 nCount(aPolyPolygon.count());

			if(nCount)
			{
				Primitive2DSequence aRetval(nCount);

				for(sal_uInt32 a(0L); a < nCount; a++)
				{
					aRetval[a] = Primitive2DReference(new PolygonMarkerPrimitive2D(aPolyPolygon.getB2DPolygon(a), getRGBColorA(), getRGBColorB(), getDiscreteDashLength()));
				}

				return aRetval;
			}
			else
			{
				return Primitive2DSequence();
			}
		}

		PolyPolygonMarkerPrimitive2D::PolyPolygonMarkerPrimitive2D(
			const basegfx::B2DPolyPolygon& rPolyPolygon, 
			const basegfx::BColor& rRGBColorA,
			const basegfx::BColor& rRGBColorB,
			double fDiscreteDashLength)
		:	BufferedDecompositionPrimitive2D(),
			maPolyPolygon(rPolyPolygon),
			maRGBColorA(rRGBColorA),
			maRGBColorB(rRGBColorB),
			mfDiscreteDashLength(fDiscreteDashLength)
		{
		}

		bool PolyPolygonMarkerPrimitive2D::operator==(const BasePrimitive2D& rPrimitive) const
		{
			if(BufferedDecompositionPrimitive2D::operator==(rPrimitive))
			{
				const PolyPolygonMarkerPrimitive2D& rCompare = (PolyPolygonMarkerPrimitive2D&)rPrimitive;

				return (getB2DPolyPolygon() == rCompare.getB2DPolyPolygon() 
					&& getRGBColorA() == rCompare.getRGBColorA()
					&& getRGBColorB() == rCompare.getRGBColorB()
					&& getDiscreteDashLength() == rCompare.getDiscreteDashLength());
			}

			return false;
		}

		basegfx::B2DRange PolyPolygonMarkerPrimitive2D::getB2DRange(const geometry::ViewInformation2D& /*rViewInformation*/) const
		{
			// return range
			return basegfx::tools::getRange(getB2DPolyPolygon());
		}

		// provide unique ID
		ImplPrimitrive2DIDBlock(PolyPolygonMarkerPrimitive2D, PRIMITIVE2D_ID_POLYPOLYGONMARKERPRIMITIVE2D)

	} // end of namespace primitive2d
} // end of namespace drawinglayer

//////////////////////////////////////////////////////////////////////////////

namespace drawinglayer
{
	namespace primitive2d
	{
		Primitive2DSequence PolyPolygonStrokePrimitive2D::create2DDecomposition(const geometry::ViewInformation2D& /*rViewInformation*/) const
		{
			const basegfx::B2DPolyPolygon aPolyPolygon(getB2DPolyPolygon());
			const sal_uInt32 nCount(aPolyPolygon.count());

			if(nCount)
			{
				Primitive2DSequence aRetval(nCount);

				for(sal_uInt32 a(0L); a < nCount; a++)
				{
					aRetval[a] = Primitive2DReference(
                        new PolygonStrokePrimitive2D(
                            aPolyPolygon.getB2DPolygon(a), getLineAttribute(), getStrokeAttribute()));
				}

				return aRetval;
			}
			else
			{
				return Primitive2DSequence();
			}
		}

		PolyPolygonStrokePrimitive2D::PolyPolygonStrokePrimitive2D(
			const basegfx::B2DPolyPolygon& rPolyPolygon, 
  			const attribute::LineAttribute& rLineAttribute,
			const attribute::StrokeAttribute& rStrokeAttribute)
		:	BufferedDecompositionPrimitive2D(),
			maPolyPolygon(rPolyPolygon),
            maLineAttribute(rLineAttribute),
			maStrokeAttribute(rStrokeAttribute)
		{
		}

		PolyPolygonStrokePrimitive2D::PolyPolygonStrokePrimitive2D(
			const basegfx::B2DPolyPolygon& rPolyPolygon, 
  			const attribute::LineAttribute& rLineAttribute)
		:	BufferedDecompositionPrimitive2D(),
			maPolyPolygon(rPolyPolygon),
            maLineAttribute(rLineAttribute),
			maStrokeAttribute()
		{
		}

		bool PolyPolygonStrokePrimitive2D::operator==(const BasePrimitive2D& rPrimitive) const
		{
			if(BufferedDecompositionPrimitive2D::operator==(rPrimitive))
			{
				const PolyPolygonStrokePrimitive2D& rCompare = (PolyPolygonStrokePrimitive2D&)rPrimitive;

				return (getB2DPolyPolygon() == rCompare.getB2DPolyPolygon() 
					&& getLineAttribute() == rCompare.getLineAttribute()
					&& getStrokeAttribute() == rCompare.getStrokeAttribute());
			}

			return false;
		}

		basegfx::B2DRange PolyPolygonStrokePrimitive2D::getB2DRange(const geometry::ViewInformation2D& /*rViewInformation*/) const
		{
			// get range of it (subdivided)
			basegfx::B2DRange aRetval(basegfx::tools::getRange(getB2DPolyPolygon()));

			// if width, grow by line width
			if(getLineAttribute().getWidth())
			{
				aRetval.grow(getLineAttribute().getWidth() / 2.0);
			}

			return aRetval;
		}

		// provide unique ID
		ImplPrimitrive2DIDBlock(PolyPolygonStrokePrimitive2D, PRIMITIVE2D_ID_POLYPOLYGONSTROKEPRIMITIVE2D)

	} // end of namespace primitive2d
} // end of namespace drawinglayer

//////////////////////////////////////////////////////////////////////////////

namespace drawinglayer
{
	namespace primitive2d
	{
		Primitive2DSequence PolyPolygonStrokeArrowPrimitive2D::create2DDecomposition(const geometry::ViewInformation2D& /*rViewInformation*/) const
		{
			const basegfx::B2DPolyPolygon aPolyPolygon(getB2DPolyPolygon());
			const sal_uInt32 nCount(aPolyPolygon.count());

			if(nCount)
			{
				Primitive2DSequence aRetval(nCount);

				for(sal_uInt32 a(0L); a < nCount; a++)
				{
					const basegfx::B2DPolygon aPolygon(aPolyPolygon.getB2DPolygon(a));

					if(aPolygon.isClosed())
					{
						// no need for PolygonStrokeArrowPrimitive2D when polygon is closed
						aRetval[a] = Primitive2DReference(
                            new PolygonStrokePrimitive2D(aPolygon, getLineAttribute(), getStrokeAttribute()));
					}
					else
					{
						aRetval[a] = Primitive2DReference(
                            new PolygonStrokeArrowPrimitive2D(aPolygon, getLineAttribute(), 
                                getStrokeAttribute(), getStart(), getEnd()));
					}
				}

				return aRetval;
			}
			else
			{
				return Primitive2DSequence();
			}
		}

		PolyPolygonStrokeArrowPrimitive2D::PolyPolygonStrokeArrowPrimitive2D(
			const basegfx::B2DPolyPolygon& rPolyPolygon, 
   			const attribute::LineAttribute& rLineAttribute,
			const attribute::StrokeAttribute& rStrokeAttribute, 
			const attribute::LineStartEndAttribute& rStart, 
			const attribute::LineStartEndAttribute& rEnd)
		:	PolyPolygonStrokePrimitive2D(rPolyPolygon, rLineAttribute, rStrokeAttribute),
			maStart(rStart),
			maEnd(rEnd)
		{
		}

		PolyPolygonStrokeArrowPrimitive2D::PolyPolygonStrokeArrowPrimitive2D(
			const basegfx::B2DPolyPolygon& rPolyPolygon, 
   			const attribute::LineAttribute& rLineAttribute,
			const attribute::LineStartEndAttribute& rStart, 
			const attribute::LineStartEndAttribute& rEnd)
		:	PolyPolygonStrokePrimitive2D(rPolyPolygon, rLineAttribute),
			maStart(rStart),
			maEnd(rEnd)
		{
		}

		bool PolyPolygonStrokeArrowPrimitive2D::operator==(const BasePrimitive2D& rPrimitive) const
		{
			if(PolyPolygonStrokePrimitive2D::operator==(rPrimitive))
			{
				const PolyPolygonStrokeArrowPrimitive2D& rCompare = (PolyPolygonStrokeArrowPrimitive2D&)rPrimitive;

				return (getStart() == rCompare.getStart() 
					&& getEnd() == rCompare.getEnd());
			}

			return false;
		}

		basegfx::B2DRange PolyPolygonStrokeArrowPrimitive2D::getB2DRange(const geometry::ViewInformation2D& rViewInformation) const
		{
			basegfx::B2DRange aRetval;

			if(getStart().isActive() || getEnd().isActive())
			{
				// use decomposition when line start/end is used
				return BufferedDecompositionPrimitive2D::getB2DRange(rViewInformation);
			}
			else
			{
				// get range from parent
				return PolyPolygonStrokePrimitive2D::getB2DRange(rViewInformation);
			}
		}

		// provide unique ID
		ImplPrimitrive2DIDBlock(PolyPolygonStrokeArrowPrimitive2D, PRIMITIVE2D_ID_POLYPOLYGONSTROKEARROWPRIMITIVE2D)

	} // end of namespace primitive2d
} // end of namespace drawinglayer

//////////////////////////////////////////////////////////////////////////////

namespace drawinglayer
{
	namespace primitive2d
	{
		PolyPolygonColorPrimitive2D::PolyPolygonColorPrimitive2D(
			const basegfx::B2DPolyPolygon& rPolyPolygon, 
			const basegfx::BColor& rBColor)
		:	BasePrimitive2D(),
			maPolyPolygon(rPolyPolygon),
			maBColor(rBColor)
		{
		}

		bool PolyPolygonColorPrimitive2D::operator==(const BasePrimitive2D& rPrimitive) const
		{
			if(BasePrimitive2D::operator==(rPrimitive))
			{
				const PolyPolygonColorPrimitive2D& rCompare = (PolyPolygonColorPrimitive2D&)rPrimitive;

				return (getB2DPolyPolygon() == rCompare.getB2DPolyPolygon() 
					&& getBColor() == rCompare.getBColor());
			}

			return false;
		}

		basegfx::B2DRange PolyPolygonColorPrimitive2D::getB2DRange(const geometry::ViewInformation2D& /*rViewInformation*/) const
		{
			// return range
			return basegfx::tools::getRange(getB2DPolyPolygon());
		}

		// provide unique ID
		ImplPrimitrive2DIDBlock(PolyPolygonColorPrimitive2D, PRIMITIVE2D_ID_POLYPOLYGONCOLORPRIMITIVE2D)

	} // end of namespace primitive2d
} // end of namespace drawinglayer

//////////////////////////////////////////////////////////////////////////////

namespace drawinglayer
{
	namespace primitive2d
	{
		Primitive2DSequence PolyPolygonGradientPrimitive2D::create2DDecomposition(const geometry::ViewInformation2D& /*rViewInformation*/) const
		{
            if(!getFillGradient().isDefault())
            {
			    // create SubSequence with FillGradientPrimitive2D
			    const basegfx::B2DRange aPolyPolygonRange(getB2DPolyPolygon().getB2DRange());
			    FillGradientPrimitive2D* pNewGradient = new FillGradientPrimitive2D(aPolyPolygonRange, getFillGradient());
			    const Primitive2DReference xSubRef(pNewGradient);
			    const Primitive2DSequence aSubSequence(&xSubRef, 1L);

			    // create mask primitive
			    MaskPrimitive2D* pNewMask = new MaskPrimitive2D(getB2DPolyPolygon(), aSubSequence);
			    const Primitive2DReference xRef(pNewMask);
			 
                return Primitive2DSequence(&xRef, 1);
            }
            else
            {
                return Primitive2DSequence();
            }
		}

		PolyPolygonGradientPrimitive2D::PolyPolygonGradientPrimitive2D(
			const basegfx::B2DPolyPolygon& rPolyPolygon, 
			const attribute::FillGradientAttribute& rFillGradient)
		:	BufferedDecompositionPrimitive2D(),
			maPolyPolygon(rPolyPolygon),
			maFillGradient(rFillGradient)
		{
		}

		bool PolyPolygonGradientPrimitive2D::operator==(const BasePrimitive2D& rPrimitive) const
		{
			if(BufferedDecompositionPrimitive2D::operator==(rPrimitive))
			{
				const PolyPolygonGradientPrimitive2D& rCompare = (PolyPolygonGradientPrimitive2D&)rPrimitive;

				return (getFillGradient() == rCompare.getFillGradient());
			}

			return false;
		}

		// provide unique ID
		ImplPrimitrive2DIDBlock(PolyPolygonGradientPrimitive2D, PRIMITIVE2D_ID_POLYPOLYGONGRADIENTPRIMITIVE2D)

	} // end of namespace primitive2d
} // end of namespace drawinglayer

//////////////////////////////////////////////////////////////////////////////

namespace drawinglayer
{
	namespace primitive2d
	{
		Primitive2DSequence PolyPolygonHatchPrimitive2D::create2DDecomposition(const geometry::ViewInformation2D& /*rViewInformation*/) const
		{
            if(!getFillHatch().isDefault())
            {
			    // create SubSequence with FillHatchPrimitive2D
			    const basegfx::B2DRange aPolyPolygonRange(getB2DPolyPolygon().getB2DRange());
			    FillHatchPrimitive2D* pNewHatch = new FillHatchPrimitive2D(aPolyPolygonRange, getBackgroundColor(), getFillHatch());
			    const Primitive2DReference xSubRef(pNewHatch);
			    const Primitive2DSequence aSubSequence(&xSubRef, 1L);

			    // create mask primitive
			    MaskPrimitive2D* pNewMask = new MaskPrimitive2D(getB2DPolyPolygon(), aSubSequence);
			    const Primitive2DReference xRef(pNewMask);

                return Primitive2DSequence(&xRef, 1);
            }
            else
            {
                return Primitive2DSequence();
            }
		}

		PolyPolygonHatchPrimitive2D::PolyPolygonHatchPrimitive2D(
			const basegfx::B2DPolyPolygon& rPolyPolygon, 
			const basegfx::BColor& rBackgroundColor,
			const attribute::FillHatchAttribute& rFillHatch)
		:	BufferedDecompositionPrimitive2D(),
			maPolyPolygon(rPolyPolygon),
			maBackgroundColor(rBackgroundColor),
			maFillHatch(rFillHatch)
		{
		}

		bool PolyPolygonHatchPrimitive2D::operator==(const BasePrimitive2D& rPrimitive) const
		{
			if(BufferedDecompositionPrimitive2D::operator==(rPrimitive))
			{
				const PolyPolygonHatchPrimitive2D& rCompare = (PolyPolygonHatchPrimitive2D&)rPrimitive;

				return (getBackgroundColor() == rCompare.getBackgroundColor()
					&& getFillHatch() == rCompare.getFillHatch());
			}

			return false;
		}

		// provide unique ID
		ImplPrimitrive2DIDBlock(PolyPolygonHatchPrimitive2D, PRIMITIVE2D_ID_POLYPOLYGONHATCHPRIMITIVE2D)

	} // end of namespace primitive2d
} // end of namespace drawinglayer

//////////////////////////////////////////////////////////////////////////////

namespace drawinglayer
{
	namespace primitive2d
	{
		Primitive2DSequence PolyPolygonGraphicPrimitive2D::create2DDecomposition(const geometry::ViewInformation2D& /*rViewInformation*/) const
		{
            if(!getFillGraphic().isDefault())
            {
                const Graphic& rGraphic = getFillGraphic().getGraphic();
                const GraphicType aType(rGraphic.GetType());

                // is there a bitmap or a metafile (do we have content)?
                if(GRAPHIC_BITMAP == aType || GRAPHIC_GDIMETAFILE == aType)
                {
                    const Size aPrefSize(rGraphic.GetPrefSize());

                    // does content have a size?
                    if(aPrefSize.Width() && aPrefSize.Height())
                    {
                        // create SubSequence with FillGraphicPrimitive2D based on polygon range
                        const basegfx::B2DRange aPolyPolygonRange(getB2DPolyPolygon().getB2DRange());
                        const basegfx::B2DHomMatrix aNewObjectTransform(
                            basegfx::tools::createScaleTranslateB2DHomMatrix(
                                aPolyPolygonRange.getRange(),
                                aPolyPolygonRange.getMinimum()));
                        const Primitive2DReference xSubRef(
                            new FillGraphicPrimitive2D(
                                aNewObjectTransform, 
                                getFillGraphic()));

                        // embed to mask primitive
                        const Primitive2DReference xRef(
                            new MaskPrimitive2D(
                                getB2DPolyPolygon(), 
                                Primitive2DSequence(&xSubRef, 1)));

                        return Primitive2DSequence(&xRef, 1);
                    }
                }
            }

            return Primitive2DSequence();
		}

		PolyPolygonGraphicPrimitive2D::PolyPolygonGraphicPrimitive2D(
			const basegfx::B2DPolyPolygon& rPolyPolygon, 
			const attribute::FillGraphicAttribute& rFillGraphic)
		:	BufferedDecompositionPrimitive2D(),
			maPolyPolygon(rPolyPolygon),
			maFillGraphic(rFillGraphic)
		{
		}

		bool PolyPolygonGraphicPrimitive2D::operator==(const BasePrimitive2D& rPrimitive) const
		{
			if(BufferedDecompositionPrimitive2D::operator==(rPrimitive))
			{
				const PolyPolygonGraphicPrimitive2D& rCompare = (PolyPolygonGraphicPrimitive2D&)rPrimitive;
				
				return (getFillGraphic() == rCompare.getFillGraphic());
			}

			return false;
		}

		// provide unique ID
		ImplPrimitrive2DIDBlock(PolyPolygonGraphicPrimitive2D, PRIMITIVE2D_ID_POLYPOLYGONGRAPHICPRIMITIVE2D)

	} // end of namespace primitive2d
} // end of namespace drawinglayer

//////////////////////////////////////////////////////////////////////////////
// eof
