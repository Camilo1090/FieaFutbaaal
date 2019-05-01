#pragma once

#include "Action.h"
#include "bass.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class ActionStopSound :
		public Action
	{
		RTTI_DECLARATIONS(ActionStopSound, Action)

	public:
		static const std::string FilePath;
		static const std::string IsSoundEffect;
		static Vector<Signature> Signatures();

	public:
		explicit ActionStopSound(const std::string& name = std::string());
		virtual ~ActionStopSound() = default;

		virtual gsl::owner<ActionStopSound*> Clone() const override;
		virtual void Update(WorldState& worldState);

	private:

		std::string mFilePath;
		int mIsSoundEffect;
		HSAMPLE* mSample;
	};

	CONCRETE_FACTORY(ActionStopSound, Action)
}