<?php
/** 
 * Copyright Intermesh
 * 
 * This file is part of Group-Office. You should have received a copy of the
 * Group-Office license along with Group-Office. See the file /LICENSE.TXT
 * 
 * If you have questions write an e-mail to info@intermesh.nl
 * 
 * @copyright Copyright Intermesh
 * @version $Id: RFC822.class.inc 1309 2008-11-02 12:54:30Z mschering $
 * @author Merijn Schering <mschering@intermesh.nl>
 * @package go.mail
 */

/**
 * This class is used to parse and write RFC822 compliant recipient lists
 * 
 * @version $Id: RFC822.class.inc 1309 2008-11-02 12:54:30Z mschering $
 * @author Merijn Schering <mschering@intermesh.nl>
 * @package go.mail
 */

class RFC822
{
	/**
	* The array of parsed addresses
	*
	* @var     array
	* @access  private
	*/
	var $addresses = array();
	
	/**
	* Temporary storage of personal info of an e-mail address
	*
	* @var     string
	* @access  private
	*/
	var $personal = false;
	
	/**
	* Temporary storage
	*
	* @var     string
	* @access  private
	*/
	var $buffer = '';
	
	/**
	* Bool to check if a string is quoted or not
	*
	* @var     bool
	* @access  private
	*/
	var $quote = false;
	
	/**
	* Parses an RFC822 formatted string 
	* (eg. "Merijn Schering" <mschering@intermesh.nl>)
	*
	* @param	string	$address_list	The address list to parse
	* @access public
	* @return array 	With addresses containing 'personal' and 'email'
	*/
	function parse_address_list($address_list)
	{
		//initiate addresses array
		$this->addresses = array();
		
		for($i=0;$i<strlen($address_list);$i++)
		{
			$char = $address_list[$i];	
			
			switch($char)
			{
				case '"':
					$this->handle_quote($char);
				break;
				
				case "'":
					$this->handle_quote($char);
				break;
				
				case '<':
					$this->personal = trim($this->buffer);
					$this->buffer = '';
				break;
				
				case '>':
					//do nothing		
				break;							
				
				case ',':			
					if($this->quote)
					{
						$this->buffer .= $char;				
					}else
					{
						$this->add_address();
					}
				break;
				
				case ';':			
					if($this->quote)
					{
						$this->buffer .= $char;				
					}else
					{
						$this->add_address();
					}
				break;
			

				default:
					$this->buffer .= $char;
				break;
			}			
		}
		$this->add_address();
		
		return $this->addresses;	
	}
	
	/**
	* Explodes an RFC822 formatted string 
	* (eg. "Merijn Schering" <mschering@intermesh.nl>) into an array.
	*
	* @param	string	$address_list	The address list to parse
	* @access public
	* @return array 	With addresses containing the full RFC822 formatted email address.
	*/
	function explode_address_list($address_list)
	{
		$full_addresses = array();
		
		$addresses = $this->parse_address_list($address_list);
		foreach($addresses as $address)
		{
			$full_addresses[] = $this->write_address($address['personal'], $address['email']);
		}
		return $full_addresses;
	}
	
	/**
	* Produces an RFC822 formatted string 
	* (eg. "Merijn Schering" <mschering@intermesh.nl>).
	*
	* @param	string	$personal	The personal part
	* @param	string	$email	The email address
	* @access public
	* @return string  RFC822 formatted address
	*/
	
	function write_address($personal, $email)
	{
		if($email != '')
		{
			if($personal == '')
			{
				return trim($email);
			}else
			{
				return '"'.str_replace('"', '\"', $personal).'" <'.$email.'>';
			}
		}else
		{
			return false;
		}
	}
	
	/**
	* Tidy an address string
	* (eg. "Merijn Schering" <mschering@intermesh.nl>).
	*
	* @param	string	$address_list	The address list
	* @access public
	* @return string  RFC822 formatted address list
	*/
	function reformat_address_list($address_list)
	{
		$addresses = $this->parse_address_list($address_list);
		$formatted = array();
		foreach ($addresses as $address)
		{     	
			$formatted[] = $this->write_address($address['personal'], $address['email']);	
		}
		return implode(',', $formatted);
	}
	
	/**
	* Adds the current buffers to the addresses array
	*
	* @access private
	* @return void
	*/
	function add_address()
	{
		$address['personal'] = ($this->personal && (trim($this->personal) != '')) ? trim($this->personal) : trim($this->buffer);
		$address['email'] = trim($this->buffer);
		
		if($address['email'] != '')
		{
			$this->addresses[] = $address;
		}
		$this->buffer = '';
		$this->personal = false;
	}
	
	/**
	* Hanldes a quote character (' or ")
	*
	* @access private
	* @return void
	*/
	function handle_quote($char)
	{
		if(!$this->quote)
		{
			$this->quote = $char;
		}elseif($char == $this->quote)
		{
			$this->quote = false;
		}else
		{
			$this->buffer .= $char;			
		}
	}
}
