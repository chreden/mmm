#pragma once

namespace mmm
{
	struct AssertionFailureException : public std::runtime_error
	{
	public:
		explicit AssertionFailureException( const std::string& message )
			: std::runtime_error( message )
		{

		}
	};	
	
	//Class that manages automated unit testing for Lua 
	//code. Lua scripts can register functions for the testing
	//session and then execute all tests - this can also be done
	//via the remote debugger.
	class Test
	{
	public:
		//Assert that the specified condition is true - if this fails then
		//the error message will be displayed.
		void isTrue( bool condition, const std::string& message ) const;
		//Assert that the specified condition is false - if this fails then
		//the error message will be displayed.
		void isFalse( bool condition, const std::string& message ) const; 
		//Register a new test with the test suite - this will be ran when
		//the tests are executed.
		void add( const std::string& name, luabind::object table, luabind::object function );
		//Runs all currently registered tests. Output is printed to the
		//current print output
		void runAll( );
	private:
		class TestEntry
		{
		public:
			explicit TestEntry( const std::string& name, luabind::object table, luabind::object function );
			void	 run() const;
		private:
			std::string		name_;
			luabind::object table_;
			luabind::object function_;
		};

		std::vector<TestEntry> tests_;
	};

	void test_register( lua_State* state );
}
