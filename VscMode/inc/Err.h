/**
 * @file Err.h
 *
 *  Error Code Definition
 *
 * @version $Revision$
 * @author JL Juang <jl_juang@vsigntek.com>
 * @note Copyright (c) 2021,  VitalSigns Technology CO., LTD., all rights reserved.
 * @note
*/
#ifndef __ERR_H__
#define __ERR_H__

enum ErrType
{
	NO_ERR = 0,
	/// common errors
	ERR_UNKNOWN=1,
	ERR_NO_SUCH_CMD,
	ERR_EMPTY_LINE,
	ERR_RUN_MODE_ONLY,
	ERR_USER_FAIL,
	ERR_SOFTRESET_FAIL,

	/// NACK
	ERR_NACK_FAIL = 50,

	///
	ERR_COM_CLOSED,
	ERR_SET_CMD,
	ERR_FILE_NAME_NOT_FOUND,
	ERR_FILE_OPEN_FAIL,
	ERR_FILE_RENAME_FAIL,
	ERR_FILE_DEL_FAIL,
	ERR_NO_SCRIPT,
	ERR_CMD_TOO_LONG,
	ERR_FAIL_TO_CHANGE_DIR,
	ERR_FAIL_TO_OPEN_XML,
	ERR_FAIL_TO_OPEN_FILE,	
	ERR_MKDIR_FAIL,
	ERR_FILE_FORMAT_FAIL,
	ERR_PACK_SEAL,
  ERR_COMM_ISSUE,
	///  I2C
	ERR_I2C_WW_FAIL = 100,
	ERR_I2C_WB_FAIL,  
	ERR_I2C_WP_FAIL,
	ERR_I2C_W_FAIL,

	ERR_I2C_RW_FAIL,
	ERR_I2C_RB_FAIL,	
	ERR_I2C_RP_FAIL,
	ERR_I2C_R_FAIL,

  /// calculation
	ERR_CAL_NO_LVAL=200,
	ERR_EXPR_PARSING_ERR,
	ERR_IF_PARSING_ERR,
	ERR_ENDIF_MISSING_ERR,
	ERR_LOOP_STACK_OVERFLOW,
	ERR_LOOP_BACK_FAIL,
	ERR_LOOP_FORWARD_FAIL,
	ERR_LOOP_LEVEL,
	ERR_LOOP_TIME_ARG_ERR,
	ERR_LOGIC_CMD_FAIL,
	ERR_BREAK_FAIL,
	ERR_EXPR_NULL,
	ERR_EXPR_OVER_MAX_LENGTH,

	/// argument number error
	ERR_NOT_ENOUGH_ARGS=300,
	ERR_TOO_MANY_ARGS,
	ERR_WRONG_ARG_FORMAT,
	ERR_EXCEED_BUFFER_SIZE,
	/// cmd log
	ERR_CMDLOG_FAIL,
	ERR_PER_BATCH_FAIL,
	/// ps
	ERR_OPEN_COM_FAIL,
	ERR_CMPBUF_UNEQUAL,
	ERR_INVALID_CMD,
	ERR_UNKNOWN_DEV,
	///log file error
	ERR_NO_STRING,
	ERR_CONSOLE_FAIL,

	///LunaSoft board
	ERR_NO_COMMAND=400,
	ERR_INPUT_DATA_FAIL,
	ERR_EEP_INTPUT_DATA_FAIL,
	ERR_EEP_IN_OUT_NOT_MUCH,
	ERR_EEP_NOT_HAVE_DATA,
	
  /// master 
  ERR_MASTER_NO_ITEM_FAIL,
  ERR_MASTER_CONN_FAIL,
  ERR_MASTER_CONN_REC_FAIL,
  ERR_MASTER_SCAN_FAIL,
  ERR_MASTER_MSG,

	/// ADC
	ERR_ADC_START_FAIL = 500,
	ERR_ADC_STOP_FAIL,		
	ERR_ADC_READ_FAIL,	
	
	/// SPI
	ERR_SPI_READ_FAIL = 550,	
	ERR_SPI_WRITE_FAIL,		
	
	/// argument number error
	ERR_DS_WRONG_ARGS=600,
	ERR_DS_NO_SUCH_ACTION,  	

	/// Filter
	ERR_FILTER_ID_ERR=700,
	ERR_FILTER_SETUP_ERR,  
	ERR_FILTER_EXE_ERR,    	
	ERR_FILTER_TYPE_ERR,  

	/// Widget
	ERR_WIDGET_NOT_FOUND_ERR=800,

	/// Polling
	ERR_POLL_EXECUTING=1000,

	/// Timer
	ERR_TIMER_ALREADY_STARTED = 1100,

	/// system fail
	ERR_GET_REG_FAIL,
	ERR_SET_REG_FAIL,

	/// Bridge-upgrade
	ERR_BRIDGE_FW_UPGRADE_WRITE = 1200,
	ERR_BRIDGE_FW_UPGRADE_START,
	ERR_BRIDGE_FW_UPGRADE_END,


	ERR_BLE_BUSY_TIMEOUT=1500,

	NO_ACTION_ITEM
}; 

#endif ///< for __ERR_H__
