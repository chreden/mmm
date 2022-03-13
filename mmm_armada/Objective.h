#pragma once

namespace mmm
{
	class Objective
	{
	public:
		explicit Objective( int index );
		const std::string getText() const;
		void			  setText( const std::string& value );
		bool			  getState() const;
		void			  setState( bool value );
	private:
		int index_;
	};

	void objective_register( lua_State* state );
}
