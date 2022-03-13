#pragma once

namespace mmm
{
	template < eResource Res >
	float
	Container::getResource( ) const
	{
		return callback_->get(Res);
	}

	template < eResource Res >
	void
	Container::setResource( float value )
	{
		callback_->set(Res, value);
	}
}
