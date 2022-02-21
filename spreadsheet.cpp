int main (int argc, char** argv)
{
// Perform bootstrap.
Reference <XComponentContext> componentContext = bootstrap();

// Get the Service manager for retrieving the required services.
Reference <XMultiComponentFactory> serviceManager =
componentContext->getServiceManager();

// get the desktop object
Reference <XInterface> desktop =
serviceManager->createInstanceWithContext (
OUString::createFromAscii( "com.sun.star.frame.Desktop" ),
componentContext);

// Instantiate the component loader.
Reference <XComponentLoader> compLoader (desktop, UNO_QUERY);

// File properties for the blank file.
Sequence < ::com::sun::star::beans::PropertyValue > fileProperties (2);
fileProperties[0].Name = OUString::createFromAscii ("AsTemplate");
fileProperties[0].Value <<= OUString::createFromAscii ("MS Excel 97");
fileProperties[1].Name = OUString::createFromAscii ("Hidden");
fileProperties[1].Value <<= true;

// Instantiate the component.
Reference <XComponent> component = compLoader->loadComponentFromURL (
OUString::createFromAscii("private:factory/scalc"),
OUString::createFromAscii("_default"),
0,
fileProperties);

// By this a blank spreadsheet will be loaded, in hide mode i.e. spreadsheet won't be visible to the user.

// Create instance for the srpeadsheet document.
// Thir reference can be used to perform multiple operation on the spreadsheet.
Reference <XSpreadsheetDocument> spreadDoc (component, UNO_QUERY);

// Statements for storing the data into the spreadsheet.


// Note: Argv[1] contains the path with file name.
// Convert to UNO compatible URL.
OUString documentPath;
osl::FileBase::getFileURLFromSystemPath(OUString::createFromAscii(argv[1]), documentPath);

// Now store the data to the specified file.
Reference <XStorable> docStore (spreadDoc, UNO_QUERY);
doc->storeAsURL (documentPath,
Sequence < ::com::sun::star::beans::PropertyValue >());
return 0;
}