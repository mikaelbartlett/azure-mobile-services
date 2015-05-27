// ----------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation. All rights reserved.
// ----------------------------------------------------------------------------

#import <Foundation/Foundation.h>
#import "BlockDefinitions.h"
#import "MSTableOperation.h"

@class MSSyncContext;

/// The *MSTableOperationError* class represents an error that occurred while sending a
/// a table operation (insert, etc) to the Windows Azure Mobile Service during a sync
/// event (for example a Push)
/// The most common causes of a table operation error are non success codes from the
/// server such as a precondition failed response.
@interface MSTableOperationError : NSObject

///@name Properties
///@{

/// Unique error id in table store
@property (nonatomic, readonly, nonnull) NSString *guid;

/// The name of the table the operation was being performed for
@property (nonatomic, readonly, copy, nonnull) NSString *table;

/// The type of operation being performed on the table (insert, update, delete)
@property (nonatomic, readonly) MSTableOperationTypes operation;

/// The id of the item to the operation ran for
@property (nonatomic, readonly, copy, nonnull) NSString *itemId;

/// The full item being sent to the server, this item may not always be present for all
/// operations
@property (nonatomic, readonly, copy, nullable) NSDictionary *item;

/// Represents the error code recieved while executing the table operation, see *MSError*
/// for a list of Mobile Service's error codes
@property (nonatomic, readonly) NSInteger code;

/// A description of what caused the operation to fail
@property (nonatomic, readonly, nonnull) NSString *description;

/// The HTTP status code recieved while executing the operation from the mobile service. Note:
/// this item may not be set if the operation failed before going to the server
@property (nonatomic, readonly) NSInteger statusCode;

/// When the status code is a precondition failure, this item will contain the current version
/// of the item on the server
@property (nonatomic, readonly, nullable) NSDictionary *serverItem;

///@}

/// @name Handling Errors

/// Set the handled flag to indicate that all appropriate actions for this error have been taken and the
/// error will be removed from the list
@property (nonatomic) BOOL handled;

/// Removes the pending operation so it will not be tried again the next time push is called. In addition,
/// updates the local store state
- (void) cancelOperationAndUpdateItem:(nonnull NSDictionary *)item completion:(nullable MSSyncBlock)completion;

/// Removes the pending operation so it will not be tried again the next time push is called. In addition,
/// removes the item associated with the operation from the local store
- (void) cancelOperationAndDiscardItemWithCompletion:(nullable MSSyncBlock)completion;


/// @name Initializing the MSTableOperationError Object
/// @{

/// Initializes the table operation error from the provided operation, item, error, and context objects.
- (nonnull instancetype) initWithOperation:(nonnull MSTableOperation *)operation item:(nonnull NSDictionary *)item context:(nullable MSSyncContext *)context error:(nonnull NSError *) error;

- (nonnull instancetype) initWithOperation:(nonnull MSTableOperation *)operation item:(nonnull NSDictionary *)item error:(nonnull NSError *) error __deprecated;

/// Initializes the table operation error from a serialized representation of a MSTableOperationError.
- (nonnull instancetype) initWithSerializedItem:(nonnull NSDictionary *)item context:(nullable MSSyncContext *)context;

- (nonnull instancetype) initWithSerializedItem:(nonnull NSDictionary *)item __deprecated;

///@}

/// @name Serializing the MSTableOperationError Object
/// @{

/// Returns an NSDictionary with two keys, id and properties, where properties contains a serialized version
/// of the error
- (nonnull NSDictionary *) serialize;

/// @}
@end
