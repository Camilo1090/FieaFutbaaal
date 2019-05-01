#pragma once

#include "Action.h"
#include "bass.h"
#include "Factory.h"

namespace FieaGameEngine
{
	class ActionPauseSound :
		public Action
	{
		RTTI_DECLARATIONS(ActionPauseSound, Action)

	public:
		static const std::string FilePath;
		static const std::string IsSoundEffect;
		static Vector<Signature> Signatures();

	public:
		explicit ActionPauseSound(const std::string& name = std::string());
		virtual ~ActionPauseSound() = default;

		virtual gsl::owner<ActionPauseSound*> Clone() const override;
		virtual void Update(WorldState& worldState);

	private:

		std::string mFilePath;
		int mIsSoundEffect;
		HSAMPLE* mSample;
	};

	CONCRETE_FACTORY(ActionPauseSound, Action)
}