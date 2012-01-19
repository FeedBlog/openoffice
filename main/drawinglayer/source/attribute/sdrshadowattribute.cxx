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

#include <drawinglayer/attribute/sdrshadowattribute.hxx>
#include <basegfx/vector/b2dvector.hxx>
#include <basegfx/color/bcolor.hxx>

//////////////////////////////////////////////////////////////////////////////

namespace drawinglayer
{
	namespace attribute
	{
		class ImpSdrShadowAttribute
		{
		public:
			// refcounter
			sal_uInt32								mnRefCount;

			// shadow definitions
			basegfx::B2DVector					maOffset;					// shadow offset 1/100th mm
			double								mfTransparence;				// [0.0 .. 1.0], 0.0==no transp.
			basegfx::BColor						maColor;					// color of shadow

			ImpSdrShadowAttribute(
				const basegfx::B2DVector& rOffset, 
                double fTransparence, 
                const basegfx::BColor& rColor)
			:	mnRefCount(0),
		    	maOffset(rOffset),
			    mfTransparence(fTransparence),
			    maColor(rColor)
		    {
		    }

			// data read access
			const basegfx::B2DVector& getOffset() const { return maOffset; }
			double getTransparence() const { return mfTransparence;	}
			const basegfx::BColor& getColor() const { return maColor; }

			bool operator==(const ImpSdrShadowAttribute& rCandidate) const
		    {
			    return (getOffset() == rCandidate.getOffset()
                    && getTransparence() == rCandidate.getTransparence()
				    && getColor() == rCandidate.getColor());
		    }
            
            static ImpSdrShadowAttribute* get_global_default()
            {
                static ImpSdrShadowAttribute* pDefault = 0;

                if(!pDefault)
                {
                    pDefault = new ImpSdrShadowAttribute(
                        basegfx::B2DVector(),
                        0.0, 
                        basegfx::BColor());

                    // never delete; start with RefCount 1, not 0
    			    pDefault->mnRefCount++;
                }

                return pDefault;
            }
		};

        SdrShadowAttribute::SdrShadowAttribute(
            const basegfx::B2DVector& rOffset, 
            double fTransparence, 
            const basegfx::BColor& rColor)
		:	mpSdrShadowAttribute(new ImpSdrShadowAttribute(
                rOffset, fTransparence, rColor))
		{
		}

		SdrShadowAttribute::SdrShadowAttribute()
        :	mpSdrShadowAttribute(ImpSdrShadowAttribute::get_global_default())
		{
			mpSdrShadowAttribute->mnRefCount++;
		}

        SdrShadowAttribute::SdrShadowAttribute(const SdrShadowAttribute& rCandidate)
		:	mpSdrShadowAttribute(rCandidate.mpSdrShadowAttribute)
		{
			mpSdrShadowAttribute->mnRefCount++;
		}

		SdrShadowAttribute::~SdrShadowAttribute()
		{
			if(mpSdrShadowAttribute->mnRefCount)
			{
				mpSdrShadowAttribute->mnRefCount--;
			}
			else
			{
				delete mpSdrShadowAttribute;
			}
		}

        bool SdrShadowAttribute::isDefault() const
        {
            return mpSdrShadowAttribute == ImpSdrShadowAttribute::get_global_default();
        }

        SdrShadowAttribute& SdrShadowAttribute::operator=(const SdrShadowAttribute& rCandidate)
		{
			if(rCandidate.mpSdrShadowAttribute != mpSdrShadowAttribute)
			{
				if(mpSdrShadowAttribute->mnRefCount)
				{
					mpSdrShadowAttribute->mnRefCount--;
				}
				else
				{
					delete mpSdrShadowAttribute;
				}
				
				mpSdrShadowAttribute = rCandidate.mpSdrShadowAttribute;
				mpSdrShadowAttribute->mnRefCount++;
			}

			return *this;
		}

		bool SdrShadowAttribute::operator==(const SdrShadowAttribute& rCandidate) const
		{
			if(rCandidate.mpSdrShadowAttribute == mpSdrShadowAttribute)
			{
				return true;
			}

			if(rCandidate.isDefault() != isDefault())
			{
				return false;
			}

			return (*rCandidate.mpSdrShadowAttribute == *mpSdrShadowAttribute);
		}

		const basegfx::B2DVector& SdrShadowAttribute::getOffset() const 
        { 
            return mpSdrShadowAttribute->getOffset(); 
        }

		double SdrShadowAttribute::getTransparence() const 
        { 
            return mpSdrShadowAttribute->getTransparence();	
        }

		const basegfx::BColor& SdrShadowAttribute::getColor() const 
        { 
            return mpSdrShadowAttribute->getColor(); 
        }
    } // end of namespace attribute
} // end of namespace drawinglayer

//////////////////////////////////////////////////////////////////////////////
// eof
